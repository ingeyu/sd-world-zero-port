///////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2007, Industrial Light & Magic, a division of Lucas
// Digital Ltd. LLC
// 
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
// *       Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
// *       Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
// *       Neither the name of Industrial Light & Magic nor the names of
// its contributors may be used to endorse or promote products derived
// from this software without specific prior written permission. 
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
///////////////////////////////////////////////////////////////////////////


#include <tmpDir.h>
#include <fuzzFile.h>

#include <ImfRgbaFile.h>
#include <ImfArray.h>
#include <ImfThreading.h>
#include <IlmThread.h>
#include <Iex.h>
#include <iostream>
#include <cassert>

using namespace std;
using namespace Imath;
using namespace Imf;

namespace {

void
fillPixels (Array2D<Rgba> &pixels, int w, int h)
{
    for (int y = 0; y < h; ++y)
    {
	for (int x = 0; x < w; ++x)
	{
	    Rgba &p = pixels[y][x];

	    p.r = 0.5 + 0.5 * sin (0.1 * x + 0.1 * y);
	    p.g = 0.5 + 0.5 * sin (0.1 * x + 0.2 * y);
	    p.b = 0.5 + 0.5 * sin (0.1 * x + 0.3 * y);
	    p.a = (p.r + p.b + p.g) / 3.0;
	}
    }
}


void
writeImage (const char fileName[],
	    int width,
	    int height,
	    const Array2D<Rgba> &pixels,
	    Compression comp)
{
    //
    // Save the image with the specified compression.
    //

    cout << "compression " << comp << endl;

    Header header (width, height);
    header.compression() = comp;

    RgbaOutputFile out (fileName, header, WRITE_RGBA);
    out.setFrameBuffer (&pixels[0][0], 1, width);
    out.writePixels (height);
}


void
readImage (const char fileName[])
{
    //
    // Try to read the specified file.
    // Reading should either succeed or throw an exception,
    // but it should not crash for any reason.
    //

    try
    {
	RgbaInputFile in (fileName);
	const Box2i &dw = in.dataWindow();
	
	int w = dw.max.x - dw.min.x + 1;
	int dx = dw.min.x;

	if (w > (1 << 24))
	    return;

	Array<Rgba> pixels (w);
	in.setFrameBuffer (&pixels[-dx], 1, 0);

	for (int y = dw.min.y; y <= dw.max.y; ++y)
	    in.readPixels (y);
    }
    catch (...)
    {
	// empty
    }
}


void
fuzzScanLines (int numThreads, Rand48 &random)
{
    if (IlmThread::supportsThreads())
    {
	setGlobalThreadCount (numThreads);
	cout << "\nnumber of threads: " << globalThreadCount() << endl;
    }

    Header::setMaxImageSize (10000, 10000);

    const int W = 217;
    const int H = 197;

    Array2D<Rgba> pixels (H, W);
    fillPixels (pixels, W, H);

    const char *goodFile = IMF_TMP_DIR "imf_test_file_fuzz_good.exr";
    const char *brokenFile = IMF_TMP_DIR "imf_test_file_fuzz_broken.exr";

    for (int comp = 0; comp < NUM_COMPRESSION_METHODS; ++comp)
    {
	writeImage (goodFile, W, H, pixels, Compression (comp));
	fuzzFile (goodFile, brokenFile, readImage, 5000, 3000, random);
    }

    remove (goodFile);
    remove (brokenFile);
}

} // namespace


void
testFuzzScanLines ()
{
    try
    {
	cout << "Testing scanline-based files "
		"with randomly inserted errors" << endl;

	Rand48 random (1);

	fuzzScanLines (0, random);

	if (IlmThread::supportsThreads())
	    fuzzScanLines (2, random);

	cout << "ok\n" << endl;
    }
    catch (const std::exception &e)
    {
	cerr << "ERROR -- caught exception: " << e.what() << endl;
	assert (false);
    }
}
