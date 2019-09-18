/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "Huobi/HuobiClient.h"
#include<iostream>

using namespace Huobi;
using namespace std;

int main(int argc, char** argv) {

    RequestClient* client = createRequestClient("xxx", "xxx");
    TransferFuturesRequest transferReq(
            TransferFuturesType::pro_to_futures, 
            "btc",
            Decimal("1.0"));
    long transferId = client->transferBetweenFuturesAndPro(transferReq);
    cout << "transfer Id: " << transferId << endl;
}