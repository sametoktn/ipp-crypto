;===============================================================================
; Copyright 2013-2018 Intel Corporation
; All Rights Reserved.
;
; If this  software was obtained  under the  Intel Simplified  Software License,
; the following terms apply:
;
; The source code,  information  and material  ("Material") contained  herein is
; owned by Intel Corporation or its  suppliers or licensors,  and  title to such
; Material remains with Intel  Corporation or its  suppliers or  licensors.  The
; Material  contains  proprietary  information  of  Intel or  its suppliers  and
; licensors.  The Material is protected by  worldwide copyright  laws and treaty
; provisions.  No part  of  the  Material   may  be  used,  copied,  reproduced,
; modified, published,  uploaded, posted, transmitted,  distributed or disclosed
; in any way without Intel's prior express written permission.  No license under
; any patent,  copyright or other  intellectual property rights  in the Material
; is granted to  or  conferred  upon  you,  either   expressly,  by implication,
; inducement,  estoppel  or  otherwise.  Any  license   under such  intellectual
; property rights must be express and approved by Intel in writing.
;
; Unless otherwise agreed by Intel in writing,  you may not remove or alter this
; notice or  any  other  notice   embedded  in  Materials  by  Intel  or Intel's
; suppliers or licensors in any way.
;
;
; If this  software  was obtained  under the  Apache License,  Version  2.0 (the
; "License"), the following terms apply:
;
; You may  not use this  file except  in compliance  with  the License.  You may
; obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
;
;
; Unless  required  by   applicable  law  or  agreed  to  in  writing,  software
; distributed under the License  is distributed  on an  "AS IS"  BASIS,  WITHOUT
; WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
;
; See the   License  for the   specific  language   governing   permissions  and
; limitations under the License.
;===============================================================================

; 
; 
;     Purpose:  Cryptography Primitive.
;               Low level Big Number multiplication Support
; 
;

IFNDEF _PCPBNUMUL_BASIC_INC_
_PCPBNUMUL_BASIC_INC_ = 1

include pcpmulx.inc
include pcpbnumulpp_fix.inc

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; short size (1-8 qwords) operand mla and mul operations
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;
;; 1x1 multiplication
;;
ALIGN 16
mla_1x1:
   mov      rdx, qword ptr[rcx]
   MLA_FIX  1, rdi, rsi, rbx,rbp, r8
   ret

ALIGN 16
mul_1x1:
   mov      rdx,qword ptr[rcx]
   gsmulx   rdx, rax, qword ptr[rsi]
   mov      qword ptr[rdi], rax
   mov      qword ptr[rdi+sizeof(qword)], rdx
   ret


;;
;; 2x2 multiplication
;;
ALIGN 16
mla_2x2:
   mov      rdx, qword ptr[rcx]
   MLA_FIX  2, rdi, rsi, rbx,rbp, r8,r9
   mov      rdx, qword ptr[rcx+sizeof(qword)]
   MLA_FIX  2, <rdi+sizeof(qword)>, rsi, rbx,rbp, r8,r9
   ret

ALIGN 16
mul_2x2:
   call     mla_2x2
   mov      qword ptr[rdi+sizeof(qword)*2], r8
   mov      qword ptr[rdi+sizeof(qword)*3], r9
   ret


;;
;; 3x3 multiplication
;;
ALIGN 16
mla_3x3:
   mov      rdx, qword ptr[rcx]
   MLA_FIX  3, rdi, rsi, rbx,rbp, r8,r9,r10
   mov      rdx, qword ptr[rcx+sizeof(qword)]
   MLA_FIX  3, <rdi+sizeof(qword)>, rsi, rbx,rbp, r8,r9,r10
   mov      rdx, qword ptr[rcx+sizeof(qword)*2]
   MLA_FIX  3, <rdi+sizeof(qword)*2>, rsi, rbx,rbp, r8,r9,r10
   ret

ALIGN 16
mul_3x3:
   call     mla_3x3
   mov      qword ptr[rdi+sizeof(qword)*3], r8
   mov      qword ptr[rdi+sizeof(qword)*4], r9
   mov      qword ptr[rdi+sizeof(qword)*5], r10
   ret


;;
;; 4x{2,4} multiplication
;;
ALIGN 16
mla_4x4:
   mov      rdx, qword ptr[rcx]
   MLA_FIX  4, rdi, rsi, rbx,rbp, r8,r9,r10,r11
   mov      rdx, qword ptr[rcx+sizeof(qword)]
   MLA_FIX  4, <rdi+sizeof(qword)>, rsi, rbx,rbp, r8,r9,r10,r11
   mov      rdx, qword ptr[rcx+sizeof(qword)*2]
   MLA_FIX  4, <rdi+sizeof(qword)*2>, rsi, rbx,rbp, r8,r9,r10,r11
   mov      rdx, qword ptr[rcx+sizeof(qword)*3]
   MLA_FIX  4, <rdi+sizeof(qword)*3>, rsi, rbx,rbp, r8,r9,r10,r11
   ret

ALIGN 16
mul_4x4:
   call     mla_4x4
   mov      qword ptr[rdi+sizeof(qword)*4], r8
   mov      qword ptr[rdi+sizeof(qword)*5], r9
   mov      qword ptr[rdi+sizeof(qword)*6], r10
   mov      qword ptr[rdi+sizeof(qword)*7], r11
   ret


;;
;; 5x{2,5} multiplication
;;
ALIGN 16
mla_5x5:
   mov      rdx, [rcx+sizeof(qword)*0]
   MLA_FIX  5, <rdi>, rsi, rbx,rbp, r8,r9,r10,r11,r12
   mov      rdx, [rcx+sizeof(qword)*1]
   MLA_FIX  5, <rdi+sizeof(qword)*1>, rsi, rbx,rbp, r8,r9,r10,r11,r12
   mov      rdx, [rcx+sizeof(qword)*2]
   MLA_FIX  5, <rdi+sizeof(qword)*2>, rsi, rbx,rbp, r8,r9,r10,r11,r12
   mov      rdx, [rcx+sizeof(qword)*3]
   MLA_FIX  5, <rdi+sizeof(qword)*3>, rsi, rbx,rbp, r8,r9,r10,r11,r12
   mov      rdx, [rcx+sizeof(qword)*4]
   MLA_FIX  5, <rdi+sizeof(qword)*4>, rsi, rbx,rbp, r8,r9,r10,r11,r12
   ret

ALIGN 16
mul_5x5:
   call     mla_5x5
   mov      qword ptr[rdi+sizeof(qword)*5], r8
   mov      qword ptr[rdi+sizeof(qword)*6], r9
   mov      qword ptr[rdi+sizeof(qword)*7], r10
   mov      qword ptr[rdi+sizeof(qword)*8], r11
   mov      qword ptr[rdi+sizeof(qword)*9], r12
   ret


;;
;; 6x{2,6} multiplication
;;
ALIGN 16
mla_6x6:
   mov      rdx, [rcx+sizeof(qword)*0]
   MLA_FIX  6, <rdi+sizeof(qword)*0>, rsi, rbx,rbp, r8,r9,r10,r11,r12,r13
   mov      rdx, [rcx+sizeof(qword)*1]
   MLA_FIX  6, <rdi+sizeof(qword)*1>, rsi, rbx,rbp, r8,r9,r10,r11,r12,r13
   mov      rdx, [rcx+sizeof(qword)*2]
   MLA_FIX  6, <rdi+sizeof(qword)*2>, rsi, rbx,rbp, r8,r9,r10,r11,r12,r13
   mov      rdx, [rcx+sizeof(qword)*3]
   MLA_FIX  6, <rdi+sizeof(qword)*3>, rsi, rbx,rbp, r8,r9,r10,r11,r12,r13
   mov      rdx, [rcx+sizeof(qword)*4]
   MLA_FIX  6, <rdi+sizeof(qword)*4>, rsi, rbx,rbp, r8,r9,r10,r11,r12,r13
   mov      rdx, [rcx+sizeof(qword)*5]
   MLA_FIX  6, <rdi+sizeof(qword)*5>, rsi, rbx,rbp, r8,r9,r10,r11,r12,r13
   ret

ALIGN 16
mul_6x6:
   call     mla_6x6
   mov      qword ptr[rdi+sizeof(qword)*6], r8
   mov      qword ptr[rdi+sizeof(qword)*7], r9
   mov      qword ptr[rdi+sizeof(qword)*8], r10
   mov      qword ptr[rdi+sizeof(qword)*9], r11
   mov      qword ptr[rdi+sizeof(qword)*10],r12
   mov      qword ptr[rdi+sizeof(qword)*11],r13
   ret


;;
;; 7x{2,7} multiplication
;;
ALIGN 16
mla_7x7:
   mov      rdx, [rcx+sizeof(qword)*0]
   MLA_FIX  7, <rdi+sizeof(qword)*0>, rsi, rbx,rbp, r8,r9,r10,r11,r12,r13,r14
   mov      rdx, [rcx+sizeof(qword)*1]
   MLA_FIX  7, <rdi+sizeof(qword)*1>, rsi, rbx,rbp, r8,r9,r10,r11,r12,r13,r14
   mov      rdx, [rcx+sizeof(qword)*2]
   MLA_FIX  7, <rdi+sizeof(qword)*2>, rsi, rbx,rbp, r8,r9,r10,r11,r12,r13,r14
   mov      rdx, [rcx+sizeof(qword)*3]
   MLA_FIX  7, <rdi+sizeof(qword)*3>, rsi, rbx,rbp, r8,r9,r10,r11,r12,r13,r14
   mov      rdx, [rcx+sizeof(qword)*4]
   MLA_FIX  7, <rdi+sizeof(qword)*4>, rsi, rbx,rbp, r8,r9,r10,r11,r12,r13,r14
   mov      rdx, [rcx+sizeof(qword)*5]
   MLA_FIX  7, <rdi+sizeof(qword)*5>, rsi, rbx,rbp, r8,r9,r10,r11,r12,r13,r14
   mov      rdx, [rcx+sizeof(qword)*6]
   MLA_FIX  7, <rdi+sizeof(qword)*6>, rsi, rbx,rbp, r8,r9,r10,r11,r12,r13,r14
   ret

ALIGN 16
mul_7x7:
   call     mla_7x7
   mov      qword ptr[rdi+sizeof(qword)*7], r8
   mov      qword ptr[rdi+sizeof(qword)*8], r9
   mov      qword ptr[rdi+sizeof(qword)*9], r10
   mov      qword ptr[rdi+sizeof(qword)*10],r11
   mov      qword ptr[rdi+sizeof(qword)*11],r12
   mov      qword ptr[rdi+sizeof(qword)*12],r13
   mov      qword ptr[rdi+sizeof(qword)*13],r14
   ret


;;
;; 8x{1,2,3,4,5,6,7,8} multiplication
;;
ALIGN 16
mla_8x1:
   mov      rdx, [rcx]
   MLA_FIX  8, <rdi>, rsi, rbx,rbp, r8,r9,r10,r11,r12,r13,r14,r15
   ret

ALIGN 16
mla_8x2:
   mov      rdx, [rcx+sizeof(qword)*0]
   MLA_FIX  8, <rdi+sizeof(qword)*0>, rsi, rbx,rbp, r8,r9,r10,r11,r12,r13,r14,r15
   mov      rdx, [rcx+sizeof(qword)*1]
   MLA_FIX  8, <rdi+sizeof(qword)*1>, rsi, rbx,rbp, r8,r9,r10,r11,r12,r13,r14,r15
   ret

ALIGN 16
mla_8x3:
   mov      rdx, [rcx+sizeof(qword)*0]
   MLA_FIX  8, <rdi+sizeof(qword)*0>, rsi, rbx,rbp, r8,r9,r10,r11,r12,r13,r14,r15
   mov      rdx, [rcx+sizeof(qword)*1]
   MLA_FIX  8, <rdi+sizeof(qword)*1>, rsi, rbx,rbp, r8,r9,r10,r11,r12,r13,r14,r15
   mov      rdx, [rcx+sizeof(qword)*2]
   MLA_FIX  8, <rdi+sizeof(qword)*2>, rsi, rbx,rbp, r8,r9,r10,r11,r12,r13,r14,r15
   ret

ALIGN 16
mla_8x4:
   mov      rdx, [rcx+sizeof(qword)*0]
   MLA_FIX  8, <rdi+sizeof(qword)*0>, rsi, rbx,rbp, r8,r9,r10,r11,r12,r13,r14,r15
   mov      rdx, [rcx+sizeof(qword)*1]
   MLA_FIX  8, <rdi+sizeof(qword)*1>, rsi, rbx,rbp, r8,r9,r10,r11,r12,r13,r14,r15
   mov      rdx, [rcx+sizeof(qword)*2]
   MLA_FIX  8, <rdi+sizeof(qword)*2>, rsi, rbx,rbp, r8,r9,r10,r11,r12,r13,r14,r15
   mov      rdx, [rcx+sizeof(qword)*3]
   MLA_FIX  8, <rdi+sizeof(qword)*3>, rsi, rbx,rbp, r8,r9,r10,r11,r12,r13,r14,r15
   ret

ALIGN 16
mla_8x5:
   mov      rdx, [rcx+sizeof(qword)*0]
   MLA_FIX  8, <rdi+sizeof(qword)*0>, rsi, rbx,rbp, r8,r9,r10,r11,r12,r13,r14,r15
   mov      rdx, [rcx+sizeof(qword)*1]
   MLA_FIX  8, <rdi+sizeof(qword)*1>, rsi, rbx,rbp, r8,r9,r10,r11,r12,r13,r14,r15
   mov      rdx, [rcx+sizeof(qword)*2]
   MLA_FIX  8, <rdi+sizeof(qword)*2>, rsi, rbx,rbp, r8,r9,r10,r11,r12,r13,r14,r15
   mov      rdx, [rcx+sizeof(qword)*3]
   MLA_FIX  8, <rdi+sizeof(qword)*3>, rsi, rbx,rbp, r8,r9,r10,r11,r12,r13,r14,r15
   mov      rdx, [rcx+sizeof(qword)*4]
   MLA_FIX  8, <rdi+sizeof(qword)*4>, rsi, rbx,rbp, r8,r9,r10,r11,r12,r13,r14,r15
   ret

ALIGN 16
mla_8x6:
   mov      rdx, [rcx+sizeof(qword)*0]
   MLA_FIX  8, <rdi+sizeof(qword)*0>, rsi, rbx,rbp, r8,r9,r10,r11,r12,r13,r14,r15
   mov      rdx, [rcx+sizeof(qword)*1]
   MLA_FIX  8, <rdi+sizeof(qword)*1>, rsi, rbx,rbp, r8,r9,r10,r11,r12,r13,r14,r15
   mov      rdx, [rcx+sizeof(qword)*2]
   MLA_FIX  8, <rdi+sizeof(qword)*2>, rsi, rbx,rbp, r8,r9,r10,r11,r12,r13,r14,r15
   mov      rdx, [rcx+sizeof(qword)*3]
   MLA_FIX  8, <rdi+sizeof(qword)*3>, rsi, rbx,rbp, r8,r9,r10,r11,r12,r13,r14,r15
   mov      rdx, [rcx+sizeof(qword)*4]
   MLA_FIX  8, <rdi+sizeof(qword)*4>, rsi, rbx,rbp, r8,r9,r10,r11,r12,r13,r14,r15
   mov      rdx, [rcx+sizeof(qword)*5]
   MLA_FIX  8, <rdi+sizeof(qword)*5>, rsi, rbx,rbp, r8,r9,r10,r11,r12,r13,r14,r15
   ret

ALIGN 16
mla_8x7:
   mov      rdx, [rcx+sizeof(qword)*0]
   MLA_FIX  8, <rdi+sizeof(qword)*0>, rsi, rbx,rbp, r8,r9,r10,r11,r12,r13,r14,r15
   mov      rdx, [rcx+sizeof(qword)*1]
   MLA_FIX  8, <rdi+sizeof(qword)*1>, rsi, rbx,rbp, r8,r9,r10,r11,r12,r13,r14,r15
   mov      rdx, [rcx+sizeof(qword)*2]
   MLA_FIX  8, <rdi+sizeof(qword)*2>, rsi, rbx,rbp, r8,r9,r10,r11,r12,r13,r14,r15
   mov      rdx, [rcx+sizeof(qword)*3]
   MLA_FIX  8, <rdi+sizeof(qword)*3>, rsi, rbx,rbp, r8,r9,r10,r11,r12,r13,r14,r15
   mov      rdx, [rcx+sizeof(qword)*4]
   MLA_FIX  8, <rdi+sizeof(qword)*4>, rsi, rbx,rbp, r8,r9,r10,r11,r12,r13,r14,r15
   mov      rdx, [rcx+sizeof(qword)*5]
   MLA_FIX  8, <rdi+sizeof(qword)*5>, rsi, rbx,rbp, r8,r9,r10,r11,r12,r13,r14,r15
   mov      rdx, [rcx+sizeof(qword)*6]
   MLA_FIX  8, <rdi+sizeof(qword)*6>, rsi, rbx,rbp, r8,r9,r10,r11,r12,r13,r14,r15
   ret

ALIGN 16
mla_8x8:
   mov      rdx, [rcx+sizeof(qword)*0]
   MLA_FIX  8, <rdi+sizeof(qword)*0>, rsi, rbx,rbp, r8,r9,r10,r11,r12,r13,r14,r15
   mov      rdx, [rcx+sizeof(qword)*1]
   MLA_FIX  8, <rdi+sizeof(qword)*1>, rsi, rbx,rbp, r8,r9,r10,r11,r12,r13,r14,r15
   mov      rdx, [rcx+sizeof(qword)*2]
   MLA_FIX  8, <rdi+sizeof(qword)*2>, rsi, rbx,rbp, r8,r9,r10,r11,r12,r13,r14,r15
   mov      rdx, [rcx+sizeof(qword)*3]
   MLA_FIX  8, <rdi+sizeof(qword)*3>, rsi, rbx,rbp, r8,r9,r10,r11,r12,r13,r14,r15
   mov      rdx, [rcx+sizeof(qword)*4]
   MLA_FIX  8, <rdi+sizeof(qword)*4>, rsi, rbx,rbp, r8,r9,r10,r11,r12,r13,r14,r15
   mov      rdx, [rcx+sizeof(qword)*5]
   MLA_FIX  8, <rdi+sizeof(qword)*5>, rsi, rbx,rbp, r8,r9,r10,r11,r12,r13,r14,r15
   mov      rdx, [rcx+sizeof(qword)*6]
   MLA_FIX  8, <rdi+sizeof(qword)*6>, rsi, rbx,rbp, r8,r9,r10,r11,r12,r13,r14,r15
   mov      rdx, [rcx+sizeof(qword)*7]
   MLA_FIX  8, <rdi+sizeof(qword)*7>, rsi, rbx,rbp, r8,r9,r10,r11,r12,r13,r14,r15
   ret

ALIGN 16
mul_8x8:
   call     mla_8x8
   mov      qword ptr[rdi+sizeof(qword)*8], r8
   mov      qword ptr[rdi+sizeof(qword)*9], r9
   mov      qword ptr[rdi+sizeof(qword)*10],r10
   mov      qword ptr[rdi+sizeof(qword)*11],r11
   mov      qword ptr[rdi+sizeof(qword)*12],r12
   mov      qword ptr[rdi+sizeof(qword)*13],r13
   mov      qword ptr[rdi+sizeof(qword)*14],r14
   mov      qword ptr[rdi+sizeof(qword)*15],r15
   ret


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; middle size (9-16 qwords) operand mla and mul operations
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

ALIGN 16
mul_9x9:
   call     mla_8x8

   mov      rdx, [rcx+sizeof(qword)*8]
   MLA_FIX  8, <rdi+sizeof(qword)*8>, rsi, rbx,rbp, r8,r9,r10,r11,r12,r13,r14,r15
   push     r15

   mov      rdx, [rsi+sizeof(qword)*8]
   mov      r15, [rdi+sizeof(qword)*8]
   MLA_FIX  8, <rdi+sizeof(qword)*8>, rcx, rbx,rbp, r15,r8,r9,r10,r11,r12,r13,r14
   mov      qword ptr[rdi+sizeof(qword)*9], r15

   gsmulx   r15, rbp, [rcx+sizeof(qword)*8]
   pop      rax
   add      r14, rax
   adc      r15,0
   add      r14, rbp
   adc      r15, 0

   mov      qword ptr[rdi+sizeof(qword)*10],r8
   mov      qword ptr[rdi+sizeof(qword)*11],r9
   mov      qword ptr[rdi+sizeof(qword)*12],r10
   mov      qword ptr[rdi+sizeof(qword)*13],r11
   mov      qword ptr[rdi+sizeof(qword)*14],r12
   mov      qword ptr[rdi+sizeof(qword)*15],r13
   mov      qword ptr[rdi+sizeof(qword)*16],r14
   mov      qword ptr[rdi+sizeof(qword)*17],r15
   ret

ALIGN 16
mul_10x10:
; A0*B0
   call     mla_8x8
   add      rdi, sizeof(qword)*8

; + A0*B1
   add      rcx, sizeof(qword)*8
   call     mla_8x2
   push     r15
   push     r14

; + A1*B0
   add      rsi, sizeof(qword)*8
   sub      rcx, sizeof(qword)*8
   SWAP     rcx, rsi

   mov      r15, r13
   mov      r14, r12
   mov      r13, r11
   mov      r12, r10
   mov      r11, r9
   mov      r10, r8
   mov      r9, qword ptr[rdi+sizeof(qword)*1]
   mov      r8, qword ptr[rdi+sizeof(qword)*0]
   call     mla_8x2

   mov      qword ptr[rdi+sizeof(qword)*2],r8
   mov      qword ptr[rdi+sizeof(qword)*3],r9
   mov      qword ptr[rdi+sizeof(qword)*4],r10
   mov      qword ptr[rdi+sizeof(qword)*5],r11
   mov      qword ptr[rdi+sizeof(qword)*6],r12
   mov      qword ptr[rdi+sizeof(qword)*7],r13
   add      rdi, sizeof(qword)*8

   xor      r10, r10
   pop      r8
   pop      r9
   add      r8, r14
   adc      r9, r15
   adc      r10,0

; + A1*B1
   SWAP     rcx, rsi
   add      rcx, sizeof(qword)*8
   call     mla_2x2
   add      rdi, sizeof(qword)*2

   add      r8, r10
   adc      r9, 0
   mov      qword ptr[rdi+sizeof(qword)*0],r8
   mov      qword ptr[rdi+sizeof(qword)*1],r9
   ret

ALIGN 16
mul_11x11:
; A0*B0
   call     mla_8x8
   add      rdi, sizeof(qword)*8

; + A0*B1
   add      rcx, sizeof(qword)*8
   call     mla_8x3
   push     r15
   push     r14
   push     r13

; + A1*B0
   add      rsi, sizeof(qword)*8
   sub      rcx, sizeof(qword)*8
   SWAP     rcx, rsi

   mov      r15, r12
   mov      r14, r11
   mov      r13, r10
   mov      r12, r9
   mov      r11, r8
   mov      r10,qword ptr[rdi+sizeof(qword)*2]
   mov      r9, qword ptr[rdi+sizeof(qword)*1]
   mov      r8, qword ptr[rdi+sizeof(qword)*0]
   call     mla_8x3

   mov      qword ptr[rdi+sizeof(qword)*3],r8
   mov      qword ptr[rdi+sizeof(qword)*4],r9
   mov      qword ptr[rdi+sizeof(qword)*5],r10
   mov      qword ptr[rdi+sizeof(qword)*6],r11
   mov      qword ptr[rdi+sizeof(qword)*7],r12
   add      rdi, sizeof(qword)*8

   xor      r11, r11
   pop      r8
   pop      r9
   pop      r10
   add      r8, r13
   adc      r9, r14
   adc      r10,r15
   adc      r11,0

; + A1*B1
   SWAP     rcx, rsi
   add      rcx, sizeof(qword)*8
   call     mla_3x3
   add      rdi, sizeof(qword)*3

   add      r8, r11
   adc      r9, 0
   adc      r10,0
   mov      qword ptr[rdi+sizeof(qword)*0],r8
   mov      qword ptr[rdi+sizeof(qword)*1],r9
   mov      qword ptr[rdi+sizeof(qword)*2],r10
   ret

ALIGN 16
mul_12x12:
; A0*B0
   call     mla_8x8
   add      rdi, sizeof(qword)*8

; + A0*B1
   add      rcx, sizeof(qword)*8
   call     mla_8x4
   push     r15
   push     r14
   push     r13
   push     r12

; + A1*B0
   add      rsi, sizeof(qword)*8
   sub      rcx, sizeof(qword)*8
   SWAP     rcx, rsi

   mov      r15, r11
   mov      r14, r10
   mov      r13, r9
   mov      r12, r8
   mov      r11,qword ptr[rdi+sizeof(qword)*3]
   mov      r10,qword ptr[rdi+sizeof(qword)*2]
   mov      r9, qword ptr[rdi+sizeof(qword)*1]
   mov      r8, qword ptr[rdi+sizeof(qword)*0]
   call     mla_8x4

   mov      qword ptr[rdi+sizeof(qword)*4],r8
   mov      qword ptr[rdi+sizeof(qword)*5],r9
   mov      qword ptr[rdi+sizeof(qword)*6],r10
   mov      qword ptr[rdi+sizeof(qword)*7],r11
   add      rdi, sizeof(qword)*8

   xor      rax, rax
   pop      r8
   pop      r9
   pop      r10
   pop      r11
   add      r8, r12
   adc      r9, r13
   adc      r10,r14
   adc      r11,r15
   adc      rax,0
   push     rax

; + A1*B1
   SWAP     rcx, rsi
   add      rcx, sizeof(qword)*8
   call     mla_4x4
   add      rdi, sizeof(qword)*4

   pop      rax
   add      r8, rax
   adc      r9, 0
   adc      r10,0
   adc      r11,0
   mov      qword ptr[rdi+sizeof(qword)*0],r8
   mov      qword ptr[rdi+sizeof(qword)*1],r9
   mov      qword ptr[rdi+sizeof(qword)*2],r10
   mov      qword ptr[rdi+sizeof(qword)*3],r11
   ret

ALIGN 16
mul_13x13:
; A0*B0
   call     mla_8x8
   add      rdi, sizeof(qword)*8

; + A0*B1
   add      rcx, sizeof(qword)*8
   call     mla_8x5
   push     r15
   push     r14
   push     r13
   push     r12
   push     r11

; + A1*B0
   add      rsi, sizeof(qword)*8
   sub      rcx, sizeof(qword)*8
   SWAP     rcx, rsi

   mov      r15, r10
   mov      r14, r9
   mov      r13, r8
   mov      r12,qword ptr[rdi+sizeof(qword)*4]
   mov      r11,qword ptr[rdi+sizeof(qword)*3]
   mov      r10,qword ptr[rdi+sizeof(qword)*2]
   mov      r9, qword ptr[rdi+sizeof(qword)*1]
   mov      r8, qword ptr[rdi+sizeof(qword)*0]
   call     mla_8x5

   mov      qword ptr[rdi+sizeof(qword)*5], r8
   mov      qword ptr[rdi+sizeof(qword)*6], r9
   mov      qword ptr[rdi+sizeof(qword)*7], r10
   add      rdi, sizeof(qword)*8

   xor      rax, rax
   pop      r8
   pop      r9
   pop      r10
   pop      rbx
   pop      rbp
   add      r8, r11
   adc      r9, r12
   adc      r10,r13
   adc      rbx,r14
   adc      rbp,r15
   adc      rax,0
   push     rax

   mov      r11, rbx
   mov      r12, rbp

; + A1*B1
   SWAP     rcx, rsi
   add      rcx, sizeof(qword)*8
   call     mla_5x5
   add      rdi, sizeof(qword)*5

   pop      rax
   add      r8, rax
   adc      r9, 0
   adc      r10,0
   adc      r11,0
   adc      r12,0
   mov      qword ptr[rdi+sizeof(qword)*0],r8
   mov      qword ptr[rdi+sizeof(qword)*1],r9
   mov      qword ptr[rdi+sizeof(qword)*2],r10
   mov      qword ptr[rdi+sizeof(qword)*3],r11
   mov      qword ptr[rdi+sizeof(qword)*4],r12
   ret

ALIGN 16
mul_14x14:
   call     mla_7x7

   add      rdi, sizeof(qword)*7
   add      rsi, sizeof(qword)*7
   call     mla_7x7
   mov      qword ptr[rdi+sizeof(qword)*7], r8
   mov      qword ptr[rdi+sizeof(qword)*8], r9
   mov      qword ptr[rdi+sizeof(qword)*9], r10
   mov      qword ptr[rdi+sizeof(qword)*10],r11
   mov      qword ptr[rdi+sizeof(qword)*11],r12
   mov      qword ptr[rdi+sizeof(qword)*12],r13
   mov      qword ptr[rdi+sizeof(qword)*13],r14

   mov      r8, qword ptr[rdi+sizeof(qword)*0]
   mov      r9, qword ptr[rdi+sizeof(qword)*1]
   mov      r10,qword ptr[rdi+sizeof(qword)*2]
   mov      r11,qword ptr[rdi+sizeof(qword)*3]
   mov      r12,qword ptr[rdi+sizeof(qword)*4]
   mov      r13,qword ptr[rdi+sizeof(qword)*5]
   mov      r14,qword ptr[rdi+sizeof(qword)*6]

   add      rcx, sizeof(qword)*7
   sub      rsi, sizeof(qword)*7
   call     mla_7x7

   xor      rdx, rdx
   op_reg_mem add, r8, qword ptr[rdi+sizeof(qword)*7], rax
   op_reg_mem adc, r9, qword ptr[rdi+sizeof(qword)*8], rax
   op_reg_mem adc, r10,qword ptr[rdi+sizeof(qword)*9], rax
   op_reg_mem adc, r11,qword ptr[rdi+sizeof(qword)*10],rax
   op_reg_mem adc, r12,qword ptr[rdi+sizeof(qword)*11],rax
   op_reg_mem adc, r13,qword ptr[rdi+sizeof(qword)*12],rax
   op_reg_mem adc, r14,qword ptr[rdi+sizeof(qword)*13],rax
   adc      rdx, 0
   push     rdx

   add      rdi, sizeof(qword)*7
   add      rsi, sizeof(qword)*7
   call     mla_7x7

   sub      rdi, sizeof(qword)*14
   sub      rsi, sizeof(qword)*7
   sub      rcx, sizeof(qword)*7

   pop      rdx
   add      r8, rdx
   adc      r9, 0
   adc      r10, 0
   adc      r11, 0
   adc      r12, 0
   adc      r13, 0
   adc      r14, 0

   mov      qword ptr[rdi+sizeof(qword)*21],r8
   mov      qword ptr[rdi+sizeof(qword)*22],r9
   mov      qword ptr[rdi+sizeof(qword)*23],r10
   mov      qword ptr[rdi+sizeof(qword)*24],r11
   mov      qword ptr[rdi+sizeof(qword)*25],r12
   mov      qword ptr[rdi+sizeof(qword)*26],r13
   mov      qword ptr[rdi+sizeof(qword)*27],r14
   ret

ALIGN 16
mul_15x15:
; A0*B0
   call     mla_8x8
   add      rdi, sizeof(qword)*8

; + A0*B1
   add      rcx, sizeof(qword)*8
   call     mla_8x7
   mov      qword ptr[rdi+sizeof(qword)*7], r8
   mov      qword ptr[rdi+sizeof(qword)*8], r9
   mov      qword ptr[rdi+sizeof(qword)*9], r10
   mov      qword ptr[rdi+sizeof(qword)*10],r11
   mov      qword ptr[rdi+sizeof(qword)*11],r12
   mov      qword ptr[rdi+sizeof(qword)*12],r13
   mov      qword ptr[rdi+sizeof(qword)*13],r14
   mov      qword ptr[rdi+sizeof(qword)*14],r15

; + A1*B0
   add      rsi, sizeof(qword)*8
   sub      rcx, sizeof(qword)*8
   SWAP     rcx, rsi

   mov      r8, qword ptr[rdi+sizeof(qword)*0]
   mov      r9, qword ptr[rdi+sizeof(qword)*1]
   mov      r10,qword ptr[rdi+sizeof(qword)*2]
   mov      r11,qword ptr[rdi+sizeof(qword)*3]
   mov      r12,qword ptr[rdi+sizeof(qword)*4]
   mov      r13,qword ptr[rdi+sizeof(qword)*5]
   mov      r14,qword ptr[rdi+sizeof(qword)*6]
   mov      r15,qword ptr[rdi+sizeof(qword)*7]
   call     mla_8x7

   mov      qword ptr[rdi+sizeof(qword)*7], r8
   add      rdi, sizeof(qword)*8

; + A1*B1
   SWAP     rcx, rsi
   add      rcx, sizeof(qword)*8

   mov      r8, r9
   mov      r9, r10
   mov      r10,r11
   mov      r11,r12
   mov      r12,r13
   mov      r13,r14
   mov      r14,r15
   xor      rdx, rdx
   op_reg_mem add, r8, qword ptr[rdi+sizeof(qword)*0], rax
   op_reg_mem adc, r9, qword ptr[rdi+sizeof(qword)*1], rax
   op_reg_mem adc, r10,qword ptr[rdi+sizeof(qword)*2], rax
   op_reg_mem adc, r11,qword ptr[rdi+sizeof(qword)*3], rax
   op_reg_mem adc, r12,qword ptr[rdi+sizeof(qword)*4], rax
   op_reg_mem adc, r13,qword ptr[rdi+sizeof(qword)*5], rax
   op_reg_mem adc, r14,qword ptr[rdi+sizeof(qword)*6], rax
   adc      rdx, 0
   push     rdx

   call     mla_7x7
   add      rdi, sizeof(qword)*7

   pop      rax
   add      r8, rax
   adc      r9, 0
   adc      r10,0
   adc      r11,0
   adc      r12,0
   adc      r13,0
   adc      r14,0
   mov      qword ptr[rdi+sizeof(qword)*0],r8
   mov      qword ptr[rdi+sizeof(qword)*1],r9
   mov      qword ptr[rdi+sizeof(qword)*2],r10
   mov      qword ptr[rdi+sizeof(qword)*3],r11
   mov      qword ptr[rdi+sizeof(qword)*4],r12
   mov      qword ptr[rdi+sizeof(qword)*5],r13
   mov      qword ptr[rdi+sizeof(qword)*6],r14
   ret

ALIGN 16
mul_16x16:
   call     mla_8x8

   add      rdi, sizeof(qword)*8
   add      rsi, sizeof(qword)*8
   call     mla_8x8
   mov      qword ptr[rdi+sizeof(qword)*8], r8
   mov      qword ptr[rdi+sizeof(qword)*9], r9
   mov      qword ptr[rdi+sizeof(qword)*10],r10
   mov      qword ptr[rdi+sizeof(qword)*11],r11
   mov      qword ptr[rdi+sizeof(qword)*12],r12
   mov      qword ptr[rdi+sizeof(qword)*13],r13
   mov      qword ptr[rdi+sizeof(qword)*14],r14
   mov      qword ptr[rdi+sizeof(qword)*15],r15

   mov      r8, qword ptr[rdi+sizeof(qword)*0]
   mov      r9, qword ptr[rdi+sizeof(qword)*1]
   mov      r10,qword ptr[rdi+sizeof(qword)*2]
   mov      r11,qword ptr[rdi+sizeof(qword)*3]
   mov      r12,qword ptr[rdi+sizeof(qword)*4]
   mov      r13,qword ptr[rdi+sizeof(qword)*5]
   mov      r14,qword ptr[rdi+sizeof(qword)*6]
   mov      r15,qword ptr[rdi+sizeof(qword)*7]

   add      rcx, sizeof(qword)*8
   sub      rsi, sizeof(qword)*8
   call     mla_8x8

   xor      rdx, rdx
   op_reg_mem add, r8, qword ptr[rdi+sizeof(qword)*8], rax
   op_reg_mem adc, r9, qword ptr[rdi+sizeof(qword)*9], rax
   op_reg_mem adc, r10,qword ptr[rdi+sizeof(qword)*10],rax
   op_reg_mem adc, r11,qword ptr[rdi+sizeof(qword)*11],rax
   op_reg_mem adc, r12,qword ptr[rdi+sizeof(qword)*12],rax
   op_reg_mem adc, r13,qword ptr[rdi+sizeof(qword)*13],rax
   op_reg_mem adc, r14,qword ptr[rdi+sizeof(qword)*14],rax
   op_reg_mem adc, r15,qword ptr[rdi+sizeof(qword)*15],rax
   adc      rdx, 0
   push     rdx

   add      rdi, sizeof(qword)*8
   add      rsi, sizeof(qword)*8
   call     mla_8x8

   sub      rdi, sizeof(qword)*16
   sub      rsi, sizeof(qword)*8
   sub      rcx, sizeof(qword)*8

   pop      rdx
   add      r8, rdx
   adc      r9, 0
   adc      r10, 0
   adc      r11, 0
   adc      r12, 0
   adc      r13, 0
   adc      r14, 0
   adc      r15, 0

   mov      qword ptr[rdi+sizeof(qword)*24],r8
   mov      qword ptr[rdi+sizeof(qword)*25],r9
   mov      qword ptr[rdi+sizeof(qword)*26],r10
   mov      qword ptr[rdi+sizeof(qword)*27],r11
   mov      qword ptr[rdi+sizeof(qword)*28],r12
   mov      qword ptr[rdi+sizeof(qword)*29],r13
   mov      qword ptr[rdi+sizeof(qword)*30],r14
   mov      qword ptr[rdi+sizeof(qword)*31],r15
   ret

mul_lxl_basic  DQ    mul_1x1 - mul_lxl_basic
               DQ    mul_2x2 - mul_lxl_basic
               DQ    mul_3x3 - mul_lxl_basic
               DQ    mul_4x4 - mul_lxl_basic
               DQ    mul_5x5 - mul_lxl_basic
               DQ    mul_6x6 - mul_lxl_basic
               DQ    mul_7x7 - mul_lxl_basic
               DQ    mul_8x8 - mul_lxl_basic
               DQ    mul_9x9 - mul_lxl_basic
               DQ    mul_10x10-mul_lxl_basic
               DQ    mul_11x11-mul_lxl_basic
               DQ    mul_12x12-mul_lxl_basic
               DQ    mul_13x13-mul_lxl_basic
               DQ    mul_14x14-mul_lxl_basic
               DQ    mul_15x15-mul_lxl_basic
               DQ    mul_16x16-mul_lxl_basic

mla_lxl_short  DQ    mla_1x1 - mla_lxl_short
               DQ    mla_2x2 - mla_lxl_short
               DQ    mla_3x3 - mla_lxl_short
               DQ    mla_4x4 - mla_lxl_short
               DQ    mla_5x5 - mla_lxl_short
               DQ    mla_6x6 - mla_lxl_short
               DQ    mla_7x7 - mla_lxl_short

mla_8xl_tail   DQ    mla_8x1 - mla_8xl_tail
               DQ    mla_8x2 - mla_8xl_tail
               DQ    mla_8x3 - mla_8xl_tail
               DQ    mla_8x4 - mla_8xl_tail
               DQ    mla_8x5 - mla_8xl_tail
               DQ    mla_8x6 - mla_8xl_tail
               DQ    mla_8x7 - mla_8xl_tail

ENDIF ;; _PCPBNUMUL_BASIC_INC_
