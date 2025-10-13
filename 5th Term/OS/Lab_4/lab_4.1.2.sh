#!/bin/bash

awk -F: '{if ($5!="") print $5}' /etc/passwd > comments.txt
