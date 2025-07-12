import psycopg2
# from dotenv import load_dotenv
from flask import Flask, render_template, request, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'msk' # for flask.session to work
params = {
    "host": "0.0.0.0" ,
    "port": 5000 ,
    "debug": False
}
conn = None

def get_db_connection():
    try:
        conn = psycopg2.connect(**session['db_config'])
        return conn
    except Exception as e:
        print(f"Error connecting to PostgreSQL: {e}")
        return None

def get_tables_list():
    conn = get_db_connection()
    if not conn:
        return None
    
    try:
        with conn.cursor() as cur:
            cur.execute("""
                SELECT table_name 
                FROM information_schema.tables 
                WHERE table_schema = 'public'
                ORDER BY table_name
            """)
            return [table[0] for table in cur.fetchall()]
    except Exception as e:
        print(f"Error fetching tables: {e}")
        return None
    finally:
        conn.close()

def is_simple_query(sql_query):
    """Check if query is a simple SELECT without GROUP BY, JOIN, or other complexities"""
    normalized = " ".join(sql_query.upper().split())  # Normalize whitespace
    
    # List of clauses that make deletion unsafe
    unsafe_clauses = [
        "GROUP BY"
    ,   "JOIN"
    ,   "UNION"
    #,   "DISTINCT"
    ,   "WITH"
    ,   "SUBQUERY"
    #,   "WHERE"  # Optional - include if you want to prevent deletion with WHERE clauses
    ]
    
    if not normalized.startswith("SELECT"):
        return False
        
    return not any(clause in normalized for clause in unsafe_clauses)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/login')
def about():
    return render_template('login.html')

@app.route('/delete-row', methods=['POST'])
def delete_row():
    if 'db_config' not in session:
        return redirect(url_for('show_db_form'))
    
    try:
        table_name = request.form['table_name']
    except Exception as e:
        return render_template('db_management.html',
                            tables=get_tables_list(), 
                            error=str(e))
    
    conn = get_db_connection()
    
    try:
        with conn.cursor() as cur:
            # Get primary key columns
            cur.execute("""
                SELECT column_name 
                FROM information_schema.key_column_usage
                WHERE table_name = %s AND table_schema = 'public'
            """, (table_name,))
            primary_keys = [row[0] for row in cur.fetchall()]
            
            if not primary_keys:
                raise Exception("No primary key found for table")
            
            # Build WHERE clause only using primary keys
            conditions = []
            query_params = []
            for key in primary_keys:
                if key in request.form:
                    conditions.append(f"{key} = %s")
                    query_params.append(request.form[key])
                else:
                    raise Exception(f"Primary key value missing for {key}")
            
            
            where_clause = " AND ".join(conditions)
            query = f"DELETE FROM {table_name} WHERE {where_clause}"
            
            cur.execute(query, tuple(query_params))
            conn.commit()
            
            # Return to the table data view
            return redirect(url_for('show_table_data'), 307)  # 307 preserves POST method
    except Exception as e:
        return render_template('db_management.html',
                            tables=get_tables_list(),
                            error=f"Delete failed: {str(e)}")
    finally:
        conn.close()

@app.route('/execute-query', methods=['POST'])
def execute_query():
    sql_query = request.form['sql_query']
    conn = get_db_connection()
    if not conn:
        return render_template('db_management.html',
                               tables=get_tables_list(), 
                               error="Database connection failed")
    
    try:
        with conn.cursor() as cur:
            cur.execute(sql_query)
            
            # For SELECT queries, fetch results
            if sql_query.strip().upper().startswith('SELECT'):
                results = cur.fetchall()
                columns = [desc[0] for desc in cur.description]
                show_delete=is_simple_query(sql_query)
                is_complex_query = not show_delete if (columns and results) else False

                return render_template('db_management.html',
                                        tables=get_tables_list(), 
                                        selected_table="Your SQL Query",
                                        columns=columns,
                                        table_data=results,
                                        sql_query=sql_query,
                                        show_delete=show_delete,
                                        complex_query_warning=is_complex_query)
            else:
                conn.commit()
                return render_template('db_management.html',
                                        tables=get_tables_list(), 
                                        results=f"Query executed successfully. Rows affected: {cur.rowcount}",
                                        sql_query=sql_query)
    except Exception as e:
        return render_template('db_management.html', 
                             error=str(e),
                             sql_query=sql_query)
    finally:
        conn.close()

@app.route('/list-tables', methods=['POST'])
def list_tables():
    tables = get_tables_list()
    return render_template('db_management.html', tables=tables)

@app.route('/show-table-data', methods=['POST'])
def show_table_data():
    try:
        table_name = request.form['table_name']
    except Exception as e:
        return render_template('db_management.html',
                            tables=get_tables_list(), 
                            error=str(e))

    conn = get_db_connection()
    if not conn:
        return render_template('db_management.html', error="Database connection failed")
    
    try:
        with conn.cursor() as cur:            
            # Then get data
            cur.execute(f"SELECT * FROM {table_name} LIMIT 100")
            data = cur.fetchall()
            # Get column names IN THE CORRECT ORDER using cursor.description
            columns = [desc[0] for desc in cur.description]
            
            return render_template('db_management.html',
                                tables=get_tables_list(), 
                                selected_table=table_name,
                                columns=columns,
                                table_data=data,
                                table_name=table_name,
                                show_delete=True)
    except Exception as e:
        return render_template('db_management.html',
                            tables=get_tables_list(), 
                            error=str(e),
                            table_name=table_name)
    finally:
        conn.close()

@app.route('/db_management')
def db_management():
    if 'db_config' not in session:
        return redirect(url_for('login.html'))
    return render_template('db_management.html',
                           tables=get_tables_list())

@app.route('/submit-form', methods=['POST'])
def handle_form():
    session['db_config'] = {
        'host':     request.form['host'] or 'localhost',
        'port':     request.form['port'] or '5432',
        'database': request.form['database'],
        'user':     request.form['user'],
        'password': request.form['password']
    }
    
    try:
        conn = psycopg2.connect(**session['db_config'])
        return redirect(url_for('db_management'))
    except Exception as e:
        print("Error", f"Could not establish the connection: {e}")
        return render_template('login.html',
                               error=f"Connection failed: {e}",
                               form_data=request.form)

if __name__ == '__main__':
    app.run(debug=True)