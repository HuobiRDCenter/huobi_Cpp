#!/usr/bin/env sh

#获取openssl 大版本号 如版本号为a.b.c，此处得到a.b
openssl version | awk '{print $2}' | awk -F. '{$3=null;print $0}'| awk 'BEGIN{OFS=".";}{print $1, $2}'
