/*
 * This file is part of Maliit Plugins
 *
 * Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies). All rights reserved.
 * Copyright (C) 2012-2013 Canonical Ltd
 *
 * Contact: Mohammad Anwari <Mohammad.Anwari@nokia.com>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this list
 * of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice, this list
 * of conditions and the following disclaimer in the documentation and/or other materials
 * provided with the distribution.
 * Neither the name of Nokia Corporation nor the names of its contributors may be
 * used to endorse or promote products derived from this software without specific
 * prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
 * THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include "wordribbon.h"

namespace MaliitKeyboard {

WordRibbon::WordRibbon()
    : m_candidates()
    , m_origin()
    , m_area()
{}

bool WordRibbon::valid() const
{
    return not m_area.size().isEmpty();
}

QRect WordRibbon::rect() const
{
    return QRect(m_origin, m_area.size());
}

QPoint WordRibbon::origin() const
{
    return m_origin;
}

void WordRibbon::setOrigin(const QPoint &origin)
{
    m_origin = origin;
}

void WordRibbon::appendCandidate(const WordCandidate &candidate)
{
    m_candidates.append(candidate);
}

QVector<WordCandidate> WordRibbon::candidates() const
{
    return m_candidates;
}

QVector<WordCandidate> & WordRibbon::rCandidates()
{
    return m_candidates;
}

void WordRibbon::clearCandidates()
{
    m_candidates.clear();
}

Area WordRibbon::area() const
{
    return m_area;
}

Area & WordRibbon::rArea()
{
    return m_area;
}

void WordRibbon::setArea(const Area &area)
{
    m_area = area;
}

bool operator==(const WordRibbon &lhs,
                const WordRibbon &rhs)
{
    return (lhs.area() == rhs.area()
            && lhs.candidates() == rhs.candidates());
}

bool operator!=(const WordRibbon &lhs,
                const WordRibbon &rhs)
{
    return (not (lhs == rhs));
}

} // namespace MaliitKeyboard
