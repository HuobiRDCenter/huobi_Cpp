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

    SubUserManageResult subUserManageResult = client->subUserManage(12345, LockAction::lock);
    cout << "subUid: " << subUserManageResult.subUid << endl;
    cout << "userState: " << subUserManageResult.userState.getValue() << endl;
}
