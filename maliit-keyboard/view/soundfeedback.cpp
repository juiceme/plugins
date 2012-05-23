/*
 * This file is part of Maliit Plugins
 *
 * Copyright (C) 2012 Openismus GmbH. All rights reserved.
 *
 * Contact: maliit-discuss@lists.maliit.org
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

#include <QFeedbackFileEffect>

#include "coreutils.h"
#include "logic/style.h"
#include "soundfeedback.h"

QTM_USE_NAMESPACE

namespace MaliitKeyboard {

enum EffectIndex
{
    KeyPressEffect,
    KeyReleaseEffect,
    LayoutChangeEffect,
    KeyboardHideEffect,

    EffectsCount
};

class SoundFeedbackPrivate
{
public:
    QFeedbackFileEffect m_effects[EffectsCount];
    Style m_style;

    SoundFeedbackPrivate();
    void playEffect(EffectIndex play_index);
    void setupEffect(EffectIndex index, const QString &sounds_dir, const QByteArray &file);
};

SoundFeedbackPrivate::SoundFeedbackPrivate()
{
    const QString sounds_dir = MaliitKeyboard::CoreUtils::maliitKeyboardDataDirectory() + "/sounds/";

    /* FIXME: Let MaliitKeyboard::InputMethod set profile of
     * style. Also means we need to inject style into consumers of
     * it. */
    m_style.setProfile("nokia-n9");

    setupEffect(KeyPressEffect, sounds_dir, m_style.keyPressSound());
    setupEffect(KeyReleaseEffect, sounds_dir, m_style.keyReleaseSound());
    setupEffect(LayoutChangeEffect, sounds_dir, m_style.layoutChangeSound());
    setupEffect(KeyboardHideEffect, sounds_dir, m_style.keyboardHideSound());
}

void SoundFeedbackPrivate::playEffect(EffectIndex play_index)
{
    /* We are iterating over whole array to stop all sounds but one,
     * which will be played.  For now, there is no need to make it
     * sophisticated (separate array of effects being now played or
     * maybe differentiating between interruptible and uninterruptible
     * effects). */
    for (int index(0); index < EffectsCount; ++index) {
        QFeedbackFileEffect& effect(m_effects[index]);

        if (index == play_index) {
            effect.start();
        } else {
            effect.stop();
        }
    }
}

/* This function is only because we have to check explicitly whether
 * gotten file name is not empty. Otherwise we could get some mutex
 * lock failures somewhere in QtMobility:
 *
 * WARNING: QSoundEffect(pulseaudio): Error decoding source
 * WARNING: QSoundEffect(pulseaudio): Error decoding source
 * WARNING: QMutex::unlock: mutex lock failure: Invalid argument
 */
void SoundFeedbackPrivate::setupEffect(EffectIndex index, const QString &sounds_dir, const QByteArray &file)
{
    if (file.isEmpty()) {
        return;
    }

    m_effects[index].setSource(QUrl::fromLocalFile(sounds_dir + file));
}

SoundFeedback::SoundFeedback(QObject *parent)
    : AbstractFeedback(parent)
    , d_ptr(new SoundFeedbackPrivate)
{}

SoundFeedback::~SoundFeedback()
{}

void SoundFeedback::playPressFeedback()
{
    Q_D(SoundFeedback);

    d->playEffect(KeyPressEffect);
}

void SoundFeedback::playReleaseFeedback()
{
    Q_D(SoundFeedback);

    d->playEffect(KeyReleaseEffect);
}

void SoundFeedback::playLayoutChangeFeedback()
{
    Q_D(SoundFeedback);

    d->playEffect(LayoutChangeEffect);
}

void SoundFeedback::playKeyboardHideFeedback()
{
    Q_D(SoundFeedback);

    d->playEffect(KeyboardHideEffect);
}

} // namespace MaliitKeyboard
