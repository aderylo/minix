#!bin/bash
kill $(lsof -t -i :10122)
