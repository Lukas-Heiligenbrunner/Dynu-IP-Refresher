//
// Created by lukas on 02.08.19.
//

#pragma once

class IPRefresher {
public:
    /**
     * refresh ip address on Dynu server
     */
    void checkIPAdress(bool force);

    IPRefresher();
    explicit IPRefresher(bool loop);
};
