#!/bin/bash

ls -l *.h | awk '{print "#include ""\"""maps/"$9"\""}'
