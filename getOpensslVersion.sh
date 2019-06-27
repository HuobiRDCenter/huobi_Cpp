#!/usr/bin/env sh

openssl version | awk '{print $2}' | awk -F. '{$2=null;print $0}' | awk 'BEGIN{OFS=".";}{print $1, $2}'
