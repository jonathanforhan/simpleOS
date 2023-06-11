#!/bin/bash

make clean ; bear -- make target=x86 || make target=x86
