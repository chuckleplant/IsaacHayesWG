//
//  ofxBase64.h
//
//  Created by ISHII 2bit on 2015/09/10.
//  https://github.com/2bbb/ofxBase64
//

/*
The MIT License (MIT)

Copyright (c) 2015 ISHII 2bit

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef ofxBase64_h
#define ofxBase64_h

#include "Poco/Base64Decoder.h"
#include "Poco/Base64Encoder.h"
#include "ofMain.h"

void ofxBase64Decode(const string &base64String, ofBuffer &output) {
    stringstream ss(base64String);
    Poco::Base64Decoder base64decoder(ss);
    base64decoder >> output;
}

void ofxBase64Encode(string &base64String, const ofBuffer &input) {
    std::ostringstream str;
    Poco::Base64Encoder encoder(str);
    encoder.write(input.getBinaryBuffer(), input.size());
    encoder.close();
    base64String = str.str();
}

#endif