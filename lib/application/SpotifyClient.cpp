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

#include <ArduinoJson.hpp>

#include "Config.hpp"

SpotifyClient::SpotifyClient() : _spotify("", "") {
  // Initializing with empty strings enables runtime configuration of client id
  // and secret
}

void SpotifyClient::begin() {
  Serial.println("Initializing the Spotify library...");
  _spotify.begin();              // Start the webserver
  while (!_spotify.is_auth()) {  // Wait for the user to authenticate
    _spotify.handle_client();  // Handle the client, this is necessary otherwise
                               // the webserver won't work
  }
  Serial.println("Spotify library initialized");
}

bool SpotifyClient::isCurrentlyPlaying() { return _spotify.is_playing(); }

String SpotifyClient::getCurrentAlbumCoverUrl() {
  response currently_playing = _spotify.currently_playing();
  if (currently_playing.status_code != 200) {
    Serial.println("Spotify API called failed with status code: " +
                   String(currently_playing.status_code));
    return "";
  }
  // See
  // https://developer.spotify.com/documentation/web-api/reference/get-the-users-currently-playing-track
  if (!currently_playing.reply["item"].isNull()) {
    if (currently_playing.reply["item"].containsKey("album")) {
      if (currently_playing.reply["item"]["album"].containsKey("images")) {
#ifdef SELECT_BEST_FITTING_ALBUM_COVER
        // Iterate through all available album covers
        // The album cover which dimensions are closest to the display
        // resolution gets chosen
        int smallest_height = -1;
        int smallest_width = -1;
        String album_cover_url = "";
        for (auto image : currently_playing.reply["item"]["album"]["images"]
                              .as<JsonArray>()) {
          if (image.containsKey("height") && image.containsKey("width")) {
            int height = image["height"].as<int>();
            int width = image["width"].as<int>();
            if (smallest_height < 0 && smallest_width < 0) {
              smallest_height = height;
              smallest_width = width;
            } else {
              if (0 < (height - DISPLAY_HEIGHT) < smallest_height &&
                  0 < (width - DISPLAY_WIDTH) < smallest_width) {
                if (image.containsKey("url")) {
                  smallest_height = height - DISPLAY_HEIGHT;
                  smallest_width = width - DISPLAY_WIDTH;
                  album_cover_url = image["url"].as<String>();
                }
              }
            }
          }
        }
        return album_cover_url;
#else
        if (currently_playing.reply["item"]["album"]["images"]
                .as<JsonArray>()
                .size() > 0) {
          auto image = currently_playing.reply["item"]["album"]["images"]
                           .as<JsonArray>()[0];
          if (image.containsKey("url")) {
            return image["url"].as<String>();
          }
        } else {
          Serial.println("No album cover image in Spotify API response");
        }
#endif
      } else {
        Serial.println("Missing images key in Spotify API response");
      }
    } else {
      Serial.println("Missing album key in Spotify API response");
    }
  } else {
    Serial.println("Spotify API didn't return any currently playing songs");
  }
  return "";
}