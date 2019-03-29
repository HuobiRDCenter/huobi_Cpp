/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   gzip.h
 * Author: yuanxueqi
 *
 * Created on 2019年3月6日, 下午9:00
 */


#ifndef GZIP_H
#define GZIP_H

    
int gzDecompress(const char *src, int srcLen, const char *dst, int dstLen);


#endif
