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
        mSize(size), mPolicy(OverflowPolicy::ForgetPast),
        mPushPos(mSize - 1), mPopPos(mSize - 1),
        mUnderflow(true), mOverflow(!size), mFirstTurn(true)
    {
        if (size)
            mBuffer = new T[size];
        else
            mBuffer = nullptr;
    }

    ~RollingBuffer()
    {
        if (mBuffer)
            delete[] mBuffer;
    }

    void setOverflowPolicy(OverflowPolicy policy) { mPolicy = policy; }

    size_t size() const { return mSize; }

    size_t length() const
    {
        if (mUnderflow) // Covers mSize = 0
            return 0;

        return (mPushPos > mPopPos)?(mPushPos - mPopPos):(mSize - mPopPos + mPushPos);
    }

    bool overflow() const { return mOverflow; }
    bool underflow() const { return mUnderflow; }

    void push(T item)
    {
        if (mOverflow && mPolicy == OverflowPolicy::IgnoreFuture)
            return;

        if (!mBuffer)
            return;

        ++mPushPos;
        if (mPushPos == mSize) {
            mPushPos = 0;
            mFirstTurn = false;
        }

        mBuffer[mPushPos] = item;
        setStateAfterPush();

        if (mOverflow && mPolicy == OverflowPolicy::ForgetPast)
            advancePop();
    }

    T pop()
    {
        // In case of undeflow, return default value (This also protects nullptr mBuffer)
        if (mUnderflow)
            return T();

        advancePop();
        setStateAfterPop();

        return mBuffer[mPopPos];
    }

    // Set mPopPos to the oldest sample in buffer
    // May overflow the buffer!
    void rewind()
    {
        if (mFirstTurn) {
            resetPop();
        } else {
            mPopPos = mPushPos;
            setStateAfterPush();
        }
    }

    // Reset pop pointer to start of buffer
    void resetPop()
    {
        mPopPos = mSize - 1;
        setStateAfterPop();
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

    void advancePop()
    {
        ++mPopPos;
        if (mPopPos == mSize)
            mPopPos = 0;
    }

    void setStateAfterPop()
    {
        mOverflow = false;
        mUnderflow = (mPopPos == mPushPos);
    }

    void setStateAfterPush()
    {
        mUnderflow = false;
        mOverflow = (mPopPos == mPushPos);
    }

};

#endif // ROLLINGBUFFER_H
