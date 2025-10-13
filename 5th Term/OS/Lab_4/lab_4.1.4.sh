#!/bin/bash

sed 's/g.*/g!/g' /etc/passwd | sed 's/b.*/b!/g' | sed 's/d.*/d!/g' > edited2.txt
