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

public:
    Transaction() {};
    Transaction(int ID, string _TrackingCode, float _Amount, TransactionType _Type, TransactionStatus _Status) : TransactionID(ID), TrackingCode(_TrackingCode), Amount(_Amount),
                                                                                                                 Status(_Status), Type(_Type)
    {
        CreatedAt = time(nullptr);
    }
    
};