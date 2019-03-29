#ifndef BATCHCANCELRESULT_H
#define BATCHCANCELRESULT_H

namespace Huobi {

    /**
     * The result of batch cancel operation.
     */
    struct BatchCancelResult {
        
        /**
         * The number of cancel request sent successfully.
         */
        int successCount;
        
        /**
         * The number of cancel request failed.
         */
        int failedCount;
    };

}


#endif /* BATCHCANCELRESULT_H */

