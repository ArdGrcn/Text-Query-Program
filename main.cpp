#include "TextQuery.h"
#include "QueryResult.h"
#include "Query.h"
#include "Blob.h"
#include "BlobPtr.h"
#include <string>

int main()
{
    std::ifstream in("input.txt");
    if (in.is_open())
    {
        TextQuery tq(in);
        Query q = Query("b") | Query("a");
        auto qr = q.evaluate(tq);
        print(std::cout, qr);
    }

    Blob<std::string> b;
    BlobPtr<std::string> ptr = b;
}