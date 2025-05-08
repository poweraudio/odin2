/*
** Odin 2 Synthesizer Plugin
** Copyright (C) 2020 - 2021 TheWaveWarden
**
** Odin 2 is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** Odin 2 is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
*/

#include <typeinfo>

#include "../ConfigFileManager.h"
#include "../JuceLibraryCode/JuceHeader.h"
#include "JsonGuiProvider.h"
#include "SplineAdComponent.h"

static constexpr auto DISCOUNT_CODE = "ODIN2SPLINE";

SplineAdComponent::SplineAdComponent() : m_close_button("Close", "Close"), m_learn_more_button("LearnMore", "Learn More"), m_copy_clipboard_button("Copy", "Copy") {
	addAndMakeVisible(m_close_button);
	addAndMakeVisible(m_learn_more_button);
	//addAndMakeVisible(m_discount_code);
	addAndMakeVisible(m_copy_clipboard_button);

	m_close_button.onClick = [this] { disableAd(); };

	m_learn_more_button.onClick = [this] {
		juce::URL("https://www.thewavewarden.com/spline").launchInDefaultBrowser();
		//disableAd();
	};

	m_copy_clipboard_button.onClick = [this] {
		juce::SystemClipboard::copyTextToClipboard(DISCOUNT_CODE);
		m_copy_clipboard_button.setButtonText("Copied!");
	};

	m_discount_code.setMultiLine(false);
	m_discount_code.setReadOnly(true);
	m_discount_code.setText(DISCOUNT_CODE);
	m_discount_code.setJustification(juce::Justification::centred);

	m_discount_code.setColour(juce::TextEditor::textColourId, COL_LIGHT);
	m_discount_code.setColour(juce::TextEditor::backgroundColourId, COL_DARK);
	m_discount_code.setColour(juce::TextEditor::outlineColourId, juce::Colours::transparentBlack);
}

SplineAdComponent::~SplineAdComponent() {
}

void SplineAdComponent::disableAd() {
	setVisible(false);

	const auto num_gui_opens = ConfigFileManager::getInstance().getNumGuiOpens();
	if (num_gui_opens >= NUM_SP_AD1)
		ConfigFileManager::getInstance().setOptionSplineAd1Seen(true);
	if (num_gui_opens >= NUM_SP_AD2)
		ConfigFileManager::getInstance().setOptionSplineAd2Seen(true);

	ConfigFileManager::getInstance().saveDataToFile();
}

void SplineAdComponent::paint(Graphics &g) {
	// draw background image
	juce::Image img = juce::ImageCache::getFromMemory(BinaryData::spline_ad_png, BinaryData::spline_ad_pngSize);
	g.drawImage(img, getLocalBounds().toFloat());

	// draw discount code
	g.setColour(juce::Colours::black.withAlpha(0.4f));
	g.fillRoundedRectangle(m_discount_code.getBounds().toFloat(), 5.0f);
	g.setColour(juce::Colour(0xfff2960b));
	g.setFont(juce::Font(m_discount_code.getHeight() * 0.6f, 1));
	g.drawText(DISCOUNT_CODE, m_discount_code.getBounds(), juce::Justification::centred, false);
}

void SplineAdComponent::resized() {
	GET_LOCAL_AREA(m_close_button, "SplineAdCloseButton");
	GET_LOCAL_AREA(m_learn_more_button, "SplineAdLearnMore");
	GET_LOCAL_AREA(m_discount_code, "SplineAdDiscountCode");
	GET_LOCAL_AREA(m_copy_clipboard_button, "SplineAdCopyClipboard");

	m_discount_code.applyFontToAllText(juce::Font(m_discount_code.getHeight() * 0.75f));
}
