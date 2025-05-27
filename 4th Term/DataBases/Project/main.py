import tkinter as tk
import psycopg2
from psycopg2 import sql
from tkinter import messagebox
import pandas as pd

from db_scripts.create_db import create_all_tables, create_triggers, insert_data, create_role


class DatabaseApp:
    def __init__(self):
        self.root = tk.Tk()
        self.conn = None  # Соединение будет доступно во всём классе
        self.setup_ui()

    def setup_ui(self):
        self.root.title("Broido DB App")       # устанавливаем заголовок окна
        self.root.geometry("1200x675+200+50")  # устанавливаем размеры окна и свдиг относительно левого верхнего угла экрана
        self.root.update_idletasks()
        self.root.resizable(False, False)

        # Создаем главный контейнер для grid
        main_container = tk.Frame(self.root)
        main_container.pack(fill=tk.BOTH, expand=True)
        
        # Верхняя панель с кнопками (pack внутри своего фрейма)
        # top_panel = tk.Frame(main_container)
        # top_panel.grid(row=0, column=0, columnspan=2, sticky="ew")
        
        # tk.Button(top_panel, text="Connect to DB", 
        #           command=self.show_login_dialog).pack(side=tk.LEFT, padx=5)
        # tk.Button(top_panel, text="Load data", 
        #           command=self.load_data).pack(side=tk.LEFT, padx=5)
        
        # Фрейм для левой части сетки йоу
        left_frame = tk.Frame(main_container)
        left_frame.grid(row=1, column=0, padx=10, pady=10, sticky="nsew")
        
        # Фрейм для правой части сетки йоу
        right_frame = tk.Frame(main_container)
        right_frame.grid(row=1, column=1, padx=10, pady=10, sticky="nsew")
        
        # Настройка весов строк и колонок
        main_container.grid_rowconfigure(1, weight=1)
        main_container.grid_columnconfigure(0, weight=1)
        main_container.grid_columnconfigure(1, weight=1)

        # Левая часть: поле ввода + кнопки (используем pack внутри left_frame)
        input_label = tk.Label(left_frame, text="Enter query:", font=("Consolas", 12))
        input_label.pack(anchor="w", pady=(0, 5))
        
        self.queryArea = tk.Text(left_frame, width=30, wrap=tk.WORD, font=("Consolas", 12))
        self.queryArea.pack(fill=tk.BOTH, expand=True)
        
        self.notice_label = tk.Label(left_frame, text="", font=("Consolas", 10))
        self.notice_label.pack(fill=tk.X, pady=5)

        button_frame = tk.Frame(left_frame)
        button_frame.pack(fill=tk.X, pady=5)

        tk.Button(button_frame, text="Process Query", 
                  command=self.process_query, font=("Consolas", 12)).pack(side=tk.LEFT, padx=2)
        tk.Button(button_frame, text="Clear", 
                  command=lambda: self.output_text.delete("1.0", tk.END),  font=("Consolas", 12)).pack(side=tk.LEFT, padx=2)
        tk.Button(button_frame, text="Create DB", 
                  command=self.setup_db,  font=("Consolas", 12)).pack(side=tk.LEFT, padx=2)
        tk.Button(button_frame, text="Fill DB", 
                  command=self.fill_db,  font=("Consolas", 12)).pack(side=tk.LEFT, padx=2)
        tk.Button(button_frame, text="Enter Login Form", 
                  command=self.show_login_dialog, font=("Consolas", 12)).pack(side=tk.RIGHT, padx=2)

        # Правая часть: окно вывода
        self.output_label = tk.Label(right_frame, text="Result:", font=("Consolas", 12))
        self.output_label.pack(anchor="w", pady=(0, 5))

        self.output_text = tk.Text(right_frame, height=15, width=40, wrap=tk.NONE, font=("Consolas", 12))
        self.output_text.pack(fill=tk.BOTH, expand=True)

        # Добавляем прокрутку для вывода
        v_scroll = tk.Scrollbar(right_frame)
        v_scroll.pack(side=tk.RIGHT, fill=tk.Y)

        h_scroll = tk.Scrollbar(right_frame, orient=tk.HORIZONTAL)
        h_scroll.pack(side=tk.BOTTOM, fill=tk.X)

        self.output_text.config(
            yscrollcommand=v_scroll.set,
            xscrollcommand=h_scroll.set
        )

        v_scroll.config(command=self.output_text.yview)
        h_scroll.config(command=self.output_text.xview)

    def process_query(self):
        query = self.queryArea.get("1.0", tk.END)  # "1.0" - первая строка, нулевой символ

        if not query:
            self.notice_label.config(text="Query is empty!", fg="red")
            return

        try:
            if not self.conn:
                tk.messagebox.showwarning("Error", "You shall connect to the DB first")
                raise Exception("No DB connection")
                
            with self.conn.cursor() as cursor:
                cursor.execute(query)
                if query.lower().strip().startswith("select"):
                    self.pd_table(cursor)
                    self.notice_label["text"] = "Query completed"
                else:
                    self.conn.commit()  # Commit for INSERT/UPDATE/DELETE
                    self.notice_label.config(text="Query completed successfully", fg="green")
        except psycopg2.Error as e:
            self.notice_label["text"] = "No Query completed"
            error_message = f"""
Error Type: {type(e)}\n
Error Message: {e}\n
Error PG Code: {e.pgcode}\n
Error PG Message: {e.pgerror}\n
Error Diag: {e.diag}\n
            """
            messagebox.showerror("Error", error_message)
        except Exception as e:
            tk.messagebox.showerror("Error", f"Query error: {e}")
        
    def pd_table(self, cursor):
        data = {}
        headers = [desc[0] for desc in cursor.description]

        for row in cursor.fetchall():
            for i in range(len(headers)):
                if headers[i] not in data.keys():
                    data[headers[i]] = []
                data[headers[i]].append(row[i])
        
        df = pd.DataFrame(data)
        self.output_text.delete("1.0", tk.END)
        self.output_text.insert(tk.END, f"{df.to_string(index=False)}\n")

    def show_login_dialog(self):
        # Всплывающее окно для ввода данных подключения
        dialog = tk.Toplevel(self.root)
        dialog.title("Login form")
        dialog.geometry("400x400")
        dialog.resizable(False, False)
        
        entries = {}
        fields = ["host", "port", "database", "user", "password"]
        for field in fields:
            tk.Label(dialog, text=field.capitalize()).pack()
            entries[field] = tk.Entry(dialog, width=30, font=("Consolas", 12))
            entries[field].pack()
        
        tk.Button(dialog, text="Connect", 
                 command=lambda: self.connect_to_db(
                     {k: v.get() for k, v in entries.items()}
                 )).pack()

    def connect_to_db(self, params):
        try:
            self.conn = psycopg2.connect(**params)
            tk.messagebox.showinfo("Success", "Connection established")
        except Exception as e:
            tk.messagebox.showerror("Error", f"Could not establish the connection: {e}")

    def load_data(self):
        if not self.conn:
            tk.messagebox.showwarning("Error", "You shall connect to the DB first")
            return
        
        try:
            with self.conn.cursor() as cursor:
                cursor.execute("SELECT current_database();")
                data = cursor.fetchall()
                tk.messagebox.showinfo("Данные", f"Получено {len(data)} записей")
        except Exception as e:
            tk.messagebox.showerror("Ошибка", f"Ошибка запроса: {e}")
    
    def setup_db(self):
        # print("in setup db")
        tk.messagebox.showwarning("WARNING", "To create a DB you should connect to any other DB with a superuser (e.g. postgres)")
        try:
            if not self.conn:
                tk.messagebox.showwarning("Error", "You shall connect to the DB first")
                raise Exception("No DB connection")
            
            self.conn.autocommit = True
            with self.conn.cursor() as cursor:
                cursor.execute(sql.SQL("CREATE DATABASE {};").format(
                    sql.Identifier("driving_school"))
                    )
                
                self.notice_label["text"] = "DB was successfully created"
                return
        except Exception as e:
            tk.messagebox.showerror("Error", f"Query error: {e}")

    def fill_db(self):
        # print("in fill db")
        tk.messagebox.showwarning("NOTICE", "Now You shall connect to the driving_school DB with superuser")
        try:
            if not self.conn:
                tk.messagebox.showwarning("Error", "You shall connect to the New DB first")
                raise Exception("No DB connection")
                
            self.conn.autocommit = True
            with self.conn.cursor() as cursor:
                cursor.execute("SELECT CURRENT_DATABASE()")
                
                if "driving_school" != cursor.fetchone()[0]:
                    tk.messagebox.showwarning("Error", "You shall connect to the New DB")
                    return

                create_all_tables(cursor); print("Created Tables")
                create_triggers(cursor)  ; print("Created Trigger")
                insert_data(cursor)      ; print("Filled Tables")
                create_role(cursor)      ; print("Created Role")

                self.notice_label["text"] = "DB was successfully filled. New Role was created"
                return
        except Exception as e:
            tk.messagebox.showerror("Error", f"Query error: {e}") 

    def run(self):
        self.root.mainloop()

if __name__ == "__main__":
    app = DatabaseApp()
    app.run()