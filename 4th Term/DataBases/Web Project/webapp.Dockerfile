FROM python:3.11-slim

# ENV USERNAME=webapp
# ENV WORKING_DIR=/home/webapp
# WORKDIR ${WORKING_DIR}

RUN mkdir /webapp
WORKDIR /webapp

RUN apt-get update && apt-get install -y \
    gcc \
    libpq-dev \
    python3-tk \
    && rm -rf /var/lib/apt/lists/*

COPY flask_app/ .
COPY requirements.txt .
# COPY service_entrypoint.sh .

# RUN groupadd ${USERNAME} && \
#     useradd -g ${USERNAME} ${USERNAME}
# RUN chown -R ${USERNAME}:${USERNAME} ${WORKING_DIR}
# RUN chmod -R u=rwx,g=rwx ${WORKING_DIR}

# USER ${USERNAME}
# ENV PATH "$PATH:/home/${USERNAME}/.local/bin"

RUN pip install --upgrade pip
RUN pip install --no-cache-dir -r requirements.txt

# ENV FLASK_APP=flask_app
# RUN chmod +x service_entrypoint.sh

# WORKDIR ${WORKING_DIR}/flask_app
# RUN flask run
# RUN flask init_db

# ENTRYPOINT [ "./service_entrypoint.sh" ]

CMD ["python", "-u", "run.py"]