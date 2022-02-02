/*
Short Waves System - A numeric modular synthetizer
Copyright (C) 2021 Pierre-Yves Rollo <dev@pyrollo.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef ROLLINGBUFFER_H
#define ROLLINGBUFFER_H

#include <cstddef>

enum class OverflowPolicy {
    ForgetPast,  // Communist way
    IgnoreFuture // Capitalist way
};

template <class T>
class RollingBuffer
{
public:
    RollingBuffer(size_t size):
        mSize(size), mPolicy(OverflowPolicy::ForgetPast), mPushPos(0), mPopPos(0), mUnderflow(true), mOverflow(false), mFirstTurn(true)
    {
        mBuffer = new T[size];
    }

    ~RollingBuffer()
    {
        delete[] mBuffer;
    }

    void setOverflowPolicy(OverflowPolicy policy) { mPolicy = policy; }

    size_t size() const { return mSize; }

    size_t length() const
    {
        return (mPushPos > mPopPos)?(mPushPos - mPopPos):(mSize - mPopPos + mPushPos);
    }

    bool overflow() const { return mOverflow; }
    bool underflow() const { return mUnderflow; }

    void push(T item)
    {
        if (mOverflow && mPolicy == OverflowPolicy::IgnoreFuture)
            return;

        mBuffer[mPushPos] = item;

        ++mPushPos;
        if (mPushPos == mSize) {
            mPushPos = 0;
            mFirstTurn = false;
        }

        mUnderflow = false;
        mOverflow = (mPopPos == mPushPos);

        if (mOverflow && mPolicy == OverflowPolicy::ForgetPast)
        {
            ++mPopPos;
            if (mPopPos == mSize)
                mPopPos = 0;
        }
    }

    T pop()
    {
        // In case of undeflow, return default value
        if (mUnderflow)
            return T();

        size_t pos = mPopPos;

        ++mPopPos;
        if (mPopPos == mSize)
            mPopPos = 0;

        mOverflow = false;
        mUnderflow = (mPopPos == mPushPos);

        return mBuffer[pos];
    }

    // Set mPopPos to the oldest sample in buffer
    // May overflow the buffer!
    void rewind()
    {
        if (mFirstTurn) {
            mPopPos = 0;
            mUnderflow = !mPushPos;
            mOverflow = false;
        }
        else
        {
            mPopPos = mPushPos;
            mUnderflow = false;
            mOverflow = true;
        }
    }

private:
    size_t mSize;
    OverflowPolicy mPolicy;

    T* mBuffer;

    size_t mPushPos;
    size_t mPopPos;

    // Statuses
    bool mUnderflow;
    bool mOverflow;
    bool mFirstTurn;
};

#endif // ROLLINGBUFFER_H
