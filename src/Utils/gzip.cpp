/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "gzip.h"
#include <zlib.h>
/* Uncompress gzip data */
///* zdata 数据 nzdata 原数据长度 data 解压后数据 ndata 解压后长度 */
//int gzdecompress(Byte *zdata, unsigned int nzdata,
//                 Byte *data, unsigned int *ndata)
//{
//	z_stream strm;
//	strm.zalloc=NULL;
//	strm.zfree=NULL;
//	strm.opaque=NULL;
//	 
//	strm.avail_in = nzdata;
//	strm.avail_out = nzdata;
//	strm.next_in = (Bytef *)zdata;
//	strm.next_out = (Bytef *)data;
//	 
//	int err=-1, ret=-1;
//	err = inflateInit2(&strm, 47);
//	if (err == Z_OK){
//	    err = inflate(&strm, Z_FINISH);
//	    if (err == Z_STREAM_END){
//	        ret = strm.total_out;
//	    }
//	    else{
//	        inflateEnd(&strm);
//	        return err;
//	    }
//	}
//	else{
//	    inflateEnd(&strm);
//	    return err;
//	}
//	inflateEnd(&strm);
//	return err;
//}

int gzDecompress(const char *src, int srcLen, const char *dst, int dstLen){
	z_stream strm;
	strm.zalloc=NULL;
	strm.zfree=NULL;
	strm.opaque=NULL;
	 
	strm.avail_in = srcLen;
	strm.avail_out = dstLen;
	strm.next_in = (Bytef *)src;
	strm.next_out = (Bytef *)dst;
	 
	int err=-1, ret=-1;
	err = inflateInit2(&strm, MAX_WBITS+16);
	if (err == Z_OK){
	    err = inflate(&strm, Z_FINISH);
	    if (err == Z_STREAM_END){
	        ret = strm.total_out;
	    }
	    else{
	        inflateEnd(&strm);
	        return err;
	    }
	}
	else{
	    inflateEnd(&strm);
	    return err;
	}
	inflateEnd(&strm);
	return err;
}

