/**
 * IPrefresher library
 * - start checking ip once
 * - or in loop mode
 *
 * @author Lukas Heiligenbrunner
 * @date 06.04.2019
 */

#pragma once

namespace IPRefresher {
    /**
     * Status return-codes for startUpService
     */
    namespace Status_Code {
        const int SUCCESS = 1;
        const int ERROR = -1;
        const int ERROR_NO_INTERNET = -2;
        const int NOREFRESH = 0;
    }

    /**
     * refresh ip address on Dynu server
     */
    bool checkIPAdress(bool force);

    /**
     * start the service in loop mode
     * every 5 minutes the ip is checked an refreshed (needed for .service)
     */
    void startUpService(int interval = 300);
}