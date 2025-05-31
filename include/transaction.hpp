#include <iostream>
using namespace std;
enum class TransactionType
{
    Transfer,
    Payment
};
enum class TransactionStatus
{
    Pending,
    Completed,
    Faioled
};
class Transaction
{
    int TransactionID;
    string TrackingCode;
    float Amount;
    TransactionStatus Status;
    TransactionType Type;
    time_t CreatedAt;
};