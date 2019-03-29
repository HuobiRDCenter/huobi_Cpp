#ifndef LOAN_H
#define LOAN_H

#include "Huobi/Enums.h"
#include "Decimal.h"
#include <string>

namespace Huobi {

    /**
     * The margin order information.
     */
    struct Loan {
        /**
         * The order id.
         */
        long id;
        
        /**
         * The user id.
         */
        long userId;
        
        /**
         * The account type which created the loan order.
         */
        AccountType accountType;
        
        /**
         * The symbol, like "btcusdt".
         */
        std::string symbol;
        
        /**
         * The currency name.
         */
        std::string currency;
        
        /**
         * The amount of the origin loan.
         */
        Decimal loanAmount;
        
        /**
         * The amount of the loan left.
         */
        Decimal loanBalance;
        
        /**
         * The loan interest rate.
         */
        Decimal interestRate;
        
        /**
         * The accumulated loan interest.
         */
        Decimal interestAmount;
        
        /**
         * The amount of loan interest left.
         */
        Decimal interestBalance;
        
        /**
         * The loan stats, possible values: created, accrual, cleared, invalid.
         */
        LoanOrderStates state;
        
        /**
         * The UNIX formatted timestamp in UTC when the order was created.
         */
        long createdTimestamp;
        
        /**
         * The UNIX formatted timestamp in UTC when the last accrue happened.
         */
        long accruedTimestamp;
    };
}


#endif /* LOAN_H */

