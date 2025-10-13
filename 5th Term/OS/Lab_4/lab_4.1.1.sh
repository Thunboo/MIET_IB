#!/bin/bash

awk -F: '{print $1}' /etc/passwd > users.txt
