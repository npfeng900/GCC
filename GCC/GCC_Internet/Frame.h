//
//  Frame.h
//  GCC_Internet
//
//  Created by Niu Panfeng on 15/5/16.
//
//

#ifndef __GCC_Internet__Frame__
#define __GCC_Internet__Frame__

#include <stdio.h>

struct FrameHeader
{
    unsigned long frame_No;
    unsigned int len; 
};

#endif /* defined(__GCC_Internet__Frame__) */
