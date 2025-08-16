#include <iostream>
#include <time.h>
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
    void setTransactionID(int id) { TransactionID = id; }
    void setTrackingCode(const string &code) { TrackingCode = code; }
    void setAmount(float amount) { Amount = amount; }
    void setType(TransactionType type) { Type = type; }
    void setStatus(TransactionStatus status) { Status = status; }
    void setCreatedAt(time_t t) { CreatedAt = t; }
    int getTransactionID() const { return TransactionID; }
    string getTrackingCode() const { return TrackingCode; }
    float getAmount() const { return Amount; }
    TransactionType getType() const { return Type; }
    TransactionStatus getStatus() const { return Status; }
    time_t getCreatedAt() const { return CreatedAt; }
};