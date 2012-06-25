/*
 * This file is part of Maliit Plugins
 *
 * Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies). All rights reserved.
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

#ifndef MALIIT_KEYBOARD_TEXT_H
#define MALIIT_KEYBOARD_TEXT_H

#include <QtCore>

namespace MaliitKeyboard {
namespace Model {

//! \brief Represents the text state of the editor
//!
//! Both MaliitKeyboard::AbstractTextEditor and
//! MaliitKeyboard::Logic::AbstractWordEngine operate on the text model.
class Text
{
public:
    enum PreeditFace {
        PreeditDefault,       //!< Used when none of below cases applies.
        PreeditNoCandidates,  //!< Used when no candidates are available for misspelled word.
        PreeditKeyPress,      //!< Used for displaying the hwkbd key just pressed.
        PreeditUnconvertible, //!< Inactive preedit region, not clickable.
        PreeditActive         //!< Preedit region with active suggestions.
    };

private:
    QString m_preedit; //!< current text segment that is edited.
    QString m_surrounding; //!< text to left and right side of cursor position, in current text block.
    QString m_primary_candidate; //!< the primary candidate from the word engine.
    uint m_surrounding_offset; //!< offset of cursor position in surrounding text.
    PreeditFace m_face; //!< face of preedit.

public:
    //! C'tor
    explicit Text();

    //! Returns current preedit.
    QString preedit() const;
    //! Set current preedit.
    //! \param preedit the updated preedit.
    void setPreedit(const QString &preedit);
    //! Append to preedit.
    //! \param appendix the string to append to current preedit.
    void appendToPreedit(const QString &appendix);
    //! Commits current preedit. Insert preedit into surrounding text and
    //! updates surrounding offset to match expected cursor position.
    void commitPreedit();

    //! Returns the primary candidate, usually provided by word engine.
    QString primaryCandidate() const;
    //! Set the primary candidate.
    //! \param candidate the primary candidate
    void setPrimaryCandidate(const QString &candidate);

    //! Returns text surrounding cursor position.
    QString surrounding() const;
    //! Returns text left of cursor position. Depends on surroundingOffset.
    QString surroundingLeft() const;
    //! Returns text right of cursor position. Depends on surroundingOffset.
    QString surroundingRight() const;
    //! Set text surrounding cursor position.
    //! \param surrounding the updated surrounding text.
    void setSurrounding(const QString &surrounding);

    //! Returns offset of cursor position in surrounding text.
    uint surroundingOffset() const;
    //! Set offset of cursor position in surrounding text. Affects
    //! surroundingLeft and surroundingRight.
    //! \param offset the updated offset.
    void setSurroundingOffset(uint offset);

    //! Returns face of preedit.
    PreeditFace preeditFace() const;
    //! Sets face of preedit.
    //! \param face new face of preedit.
    void setPreeditFace(PreeditFace face);
};

}} // namespace Model, MaliitKeyboard

#endif // MALIIT_KEYBOARD_TEXT_H