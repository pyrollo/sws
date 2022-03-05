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

#ifndef RESIZEABLEROLLINGBUFFER_H
#define RESIZEABLEROLLINGBUFFER_H

#include <cstddef>
#include <mutex>

#include "rollingbuffer.h"

template <class T>
class ResizeableRollingBuffer
{
public:

    ResizeableRollingBuffer():
        mUnderflow(true), mOverflow(true),
        mPopChunk(nullptr), mPushChunk(nullptr), mPreviousChunk(nullptr)
    {}

    ~ResizeableRollingBuffer()
    {
        mPushChunk = nullptr;

        while (mPopChunk)
        {
            auto chunk = mPopChunk;
            mPopChunk = mPopChunk->mNextChunk;
            delete chunk;
        }
    }

    bool overflow() const
    {
        return mOverflow;
    }

    bool underflow()
    {
        return mUnderflow;
    }

    void resize(size_t size)
    {
        const std::lock_guard<std::mutex> lock(mMutex);
        (void)(lock);

        if (mPushChunk)
        {
            if (size == mPushChunk->size())
                return;

            if (mPushChunk->underflow())
            {
                auto chunk = mPushChunk;
                if (mPreviousChunk)
                    mPreviousChunk->mNextChunk = nullptr;
                mPushChunk = mPreviousChunk;
                if (mPopChunk == chunk)
                    mPopChunk = mPreviousChunk;
                delete chunk;
            }

        }

        if (size == 0)
        {
            mPushChunk = nullptr;
            mOverflow = true;
            // mUnderflow? mPopChunk ? Should we still pop old samples ?
            return;
        }

        auto chunk = new ResizeableRollingBufferChunk(size);
        chunk->setOverflowPolicy(OverflowPolicy::ForgetPast);

        if (mPushChunk) {
            mPushChunk->setOverflowPolicy(OverflowPolicy::IgnoreFuture);
            mPushChunk->mNextChunk = chunk;
        }
        mPreviousChunk = mPushChunk;
        mPushChunk = chunk;
        if (!mPopChunk)
            mPopChunk = chunk;

        mOverflow = mPushChunk->overflow();
        mUnderflow = mPopChunk->underflow();

        fflush(stdout);
    }

    void push(T item)
    {
        const std::lock_guard<std::mutex> lock(mMutex);
        (void)(lock);

        if (!mPushChunk)
            return;

        mPushChunk->push(item);
        mUnderflow = mPopChunk->underflow();
        mOverflow = mPushChunk->overflow();

        if (mOverflow && mPushChunk->mNextChunk)
        {
            mPushChunk = mPushChunk->mNextChunk;
            mOverflow = mPushChunk->overflow();
        }

        return;
    }

    T pop()
    {
        const std::lock_guard<std::mutex> lock(mMutex);
        (void)(lock);

        if (!mPopChunk)
            return T();

        T item = mPopChunk->pop();
        mUnderflow = mPopChunk->underflow();
        mOverflow = mPushChunk && mPushChunk->overflow();

        if (mUnderflow && mPopChunk->mNextChunk)
        {
            auto chunk = mPopChunk;
            mPopChunk = mPopChunk->mNextChunk;
            mUnderflow = mPopChunk->underflow();
            if (mPreviousChunk == chunk)
                mPreviousChunk = nullptr;
            delete chunk;
        }

        return item;
    }

private:
    class ResizeableRollingBufferChunk: public RollingBuffer<T>
    {
    public:
        ResizeableRollingBufferChunk(size_t size):
            RollingBuffer<T>(size), mNextChunk(nullptr)
        {}

        ResizeableRollingBufferChunk *mNextChunk;
    };

    std::mutex mMutex;

    bool mUnderflow;
    bool mOverflow;

    ResizeableRollingBufferChunk* mPopChunk;
    ResizeableRollingBufferChunk* mPushChunk;
    ResizeableRollingBufferChunk* mPreviousChunk;
};

#endif // RESIZEABLEROLLINGBUFFER_H
