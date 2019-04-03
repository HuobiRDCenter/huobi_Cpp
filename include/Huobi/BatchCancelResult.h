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
        int successCount = 0;
        
        /**
         * The number of cancel request failed.
         */
        int failedCount = 0;
    };

}


#endif /* BATCHCANCELRESULT_H */

