/**
 *  Copyright 2025 Niklas Meyer
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#include "SpotifyClient.hpp"

void SpotifyClient::begin() {
    _spotify.begin();//Start the webserver
    while(!_spotify.is_auth()){//Wait for the user to authenticate
        _spotify.handle_client();//Handle the client, this is necessary otherwise the webserver won't work
    }
}