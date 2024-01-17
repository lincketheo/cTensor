//
// Created by Theo Lincke on 1/16/24.
//

#ifndef CTENSOR_MATLIB_H
#define CTENSOR_MATLIB_H

#include "Matrix.h"

Matrix matMul(const Matrix &a, const Matrix &b);

Matrix matAdd(const Matrix &a, const Matrix &b);

Matrix matMulBTranspose(const Matrix &a, const Matrix &b);

Matrix matMulATranspose(const Matrix &a, const Matrix &b);

void matAdd_inline(Matrix &a, const Matrix &b);

void relu_inline(Matrix &a);

Matrix relu(const Matrix &a);

void reluPrimeFromOutput_inline(Matrix &a);

Matrix reluPrimeFromOutput(const Matrix &a);

Matrix matSub(const Matrix &a, const Matrix &b);

void matSub_inline(Matrix &a, const Matrix &b);

Matrix matScalarMult(const Matrix &a, float b);

void matScalarMult_inline(Matrix &a, float b);

Matrix matHadMul(const Matrix &a, const Matrix &b);

void matHadMul_inline(Matrix &a, const Matrix &b);

float pNorm(const Matrix& a, float p);

float squaredErrorCost(const Matrix& a, const Matrix& b);

#endif //CTENSOR_MATLIB_H
