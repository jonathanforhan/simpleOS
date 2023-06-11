#!/bin/bash

make clean ; bear -- make target=x86_64 || make target=x86_64
