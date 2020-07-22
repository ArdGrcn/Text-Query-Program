#include "Blob.h"
#include "BlobPtr.h"
#include "ConstBlobPtr.h"


template <typename T> bool operator==(const Blob<T> &lhs, const Blob<T> &rhs)
{
    return lhs.data == rhs.data;
}

template <typename T> bool operator!=(const Blob<T> &lhs, const Blob<T> &rhs)
{
    return !(lhs == rhs);
}