// Idiomatic LZ4F decompressor (WIP)

#ifdef _MSC_VER    /* Visual Studio */
#  define _CRT_SECURE_NO_WARNINGS
#endif

#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define LZ4F_DISABLE_OBSOLETE_ENUMS
#include "lz4frame.h"

#ifdef _MSC_VER    /* Visual Studio */
#  define snprintf sprintf_s
#endif


// !!!  I want to see generic success/fail code in lz4_frame.h.
// Currently, only lz4frame_static.h has LZ4F_OK_NoError and LZ4F_ERROR_GENERIC.
//
const LZ4F_errorCode_t lz4f_errorcode_ok      = (size_t) 0;
const LZ4F_errorCode_t lz4f_errorcode_generic = (size_t) -1;


struct DecompressFileContext {
    LZ4F_decompressionContext_t ctx;
    FILE*   srcFp;
    FILE*   dstFp;
    void*   srcBuf;
    void*   dstBuf;
};

typedef struct DecompressFileContext DecompressFileContext;


static LZ4F_errorCode_t decompressFile0(DecompressFileContext* dfc) {
    LZ4F_decompressOptions_t decOpt;
    LZ4F_frameInfo_t frameInfo;

    LZ4F_errorCode_t err = lz4f_errorcode_ok;
    size_t nextToLoad = 0;

    const size_t srcBufBytes = 64 * 1024;
    const size_t dstBufBytes = 64 * 1024;

    memset(&decOpt, 0, sizeof(decOpt));
    memset(&frameInfo, 0, sizeof(frameInfo));

    dfc->srcBuf = malloc(srcBufBytes);
    dfc->dstBuf = malloc(dstBufBytes);

    if(!dfc->srcFp || !dfc->dstFp || !dfc->srcBuf || !dfc->dstBuf) {
        return lz4f_errorcode_generic;
    }

    err = LZ4F_createDecompressionContext(&dfc->ctx, LZ4F_VERSION);
    if(LZ4F_isError(err)) {
        return err;
    }

    for(nextToLoad = srcBufBytes; nextToLoad; ) {
        const size_t readSize = fread(dfc->srcBuf, 1, nextToLoad, dfc->srcFp);
        size_t readPos = 0;

        if(readSize == 0) {
            // Reach end of file without endmark.
            if(nextToLoad != 0) {
                return lz4f_errorcode_generic;
            }
            break;
        }

        while(readPos < readSize && nextToLoad) {
            const char* const srcPtr = ((const char*) dfc->srcBuf) + readPos;
            size_t srcSize = readSize - readPos;
            size_t decSize = dstBufBytes;

            // decSize and srcSize are updated in LZ4F_decompress()
            nextToLoad = LZ4F_decompress(dfc->ctx, dfc->dstBuf, &decSize, srcPtr, &srcSize, &decOpt);
            if(LZ4F_isError(nextToLoad)) {
                return (LZ4F_errorCode_t) nextToLoad;
            }

            if(decSize) {
                fwrite(dfc->dstBuf, 1, decSize, dfc->dstFp);
            }
            readPos += srcSize;
        }

        if(nextToLoad > srcBufBytes) {
            nextToLoad = srcBufBytes;
        }
    }

    return (LZ4F_errorCode_t) nextToLoad;
}


LZ4F_errorCode_t decompressFile(const char* srcFilename, const char* dstFilename) {
    LZ4F_errorCode_t err = lz4f_errorcode_ok;
    LZ4F_errorCode_t err2 = lz4f_errorcode_ok;
    DecompressFileContext dfc;

    memset(&dfc, 0, sizeof(dfc));
    dfc.srcFp = fopen(srcFilename, "rb");
    dfc.dstFp = fopen(dstFilename, "wb");

    err = decompressFile0(&dfc);
    err2 = LZ4F_freeDecompressionContext(dfc.ctx);
    if(! LZ4F_isError(err)) {
        err = err2;
    }

    free(dfc.dstBuf);
    free(dfc.srcBuf);
    if(dfc.dstFp) {
        fclose(dfc.dstFp);
    }
    if(dfc.srcFp) {
        fclose(dfc.srcFp);
    }

    return err;
}


int main(int argc, char* argv[]) {
    if(argc < 2) {
        printf("lz4f_example <input-filename>\n");
    } else {
        LZ4F_errorCode_t err = lz4f_errorcode_ok;
        const char* srcFilename = argv[1];
        char dstFilename[1024];
        snprintf(dstFilename, sizeof(dstFilename), "%s.out", srcFilename);

        printf("srcFilename : [%s]\n", srcFilename);
        printf("dstFilename : [%s]\n", dstFilename);

        err = decompressFile(srcFilename, dstFilename);
        if(LZ4F_isError(err)) {
            printf("error : %s\n", LZ4F_getErrorName(err));
        }
    }
    return 0;
}
