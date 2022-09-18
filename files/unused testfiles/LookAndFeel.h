#pragma once

/**
* LEGACY CODE
* DO NOT USE IN NEW PROJECTS, USE LAF_V2
*/

struct LookAndFeel :
	public juce::LookAndFeel_V4
{
#define DBG_BOUNDS false

	enum Colours
	{
		textColour = 13513513,
		lineColour = 15151515,
		shadowColour = 1354352,
		darkShadowColour = 7546322,
		sliderFillGradientColour1 = 3155789,
		sliderFillGradientColour2 = 3155789,

		bright = 121212,
		mediumGrey = 131313,
		mediumDarkGrey = 161613,
        semiDarkGrey = 468785,
        shade3 = semiDarkGrey,
        darkGrey = 141414,
        shade6 = darkGrey,
		moduleAdderGrey,
		warning,
		warningDark,

		
		shade2, 

		buttonDownColour,
		buttonUpColour,
		buttonBackgroundColour,

		nodeBGColour,

		preColour = 631513,
		postColour = 999080,

		bandColour1 = 91111,
		bandColour2 = 91112,
		bandColour3 = 91113,
		bandColour4 = 91114,
		bandColour5 = 91115,
		bandColour6 = 91116,
		bandColour7 = 91117,
		bandColour8 = 91118,
		bandColour9 = 91119,
		bandColour10 = 91120,

		transientColour = 92111,
		sustainColour	= 92112,	

		envelopeAnalyzerFillColour = 362674653
	};

	enum FontSizes {
        S = 14,
        M = 16,
        L = 18,
        XL = 22
    };

	LookAndFeel()
	{
		//general
		setColour(juce::ResizableWindow::backgroundColourId, juce::Colour::fromString("#FF2F2F2F")); //also slider bg color
		setColour(textColour,	juce::Colour::fromString("#FFFFFFFF"));
		setColour(lineColour,	juce::Colour::fromString("#FF767676"));
		setColour(shadowColour, juce::Colours::black.withAlpha(0.15f));								//shadowcolour

		setColour(darkShadowColour, juce::Colours::black.withAlpha(0.4f));		//dark shadowcolour for small shadows
		setColour(bright,			juce::Colours::white);
		setColour(mediumGrey,		juce::Colour::fromString("#FFC1C1C1"));
		setColour(mediumDarkGrey,	juce::Colour::fromString("#FF222222"));
		setColour(darkGrey,			juce::Colour::fromString("#FF1A1A1A"));
		setColour(semiDarkGrey,		juce::Colour::fromString("#FF616161"));
		setColour(shade2,			juce::Colour::fromString("#FF989898"));

		setColour(warning,			juce::Colour::fromString("#FFFF3131"));
		setColour(warningDark,		juce::Colour::fromString("#FF5E2121"));

		setColour(moduleAdderGrey, findColour(semiDarkGrey));

		//band colours
		setColour(preColour	,  juce::Colour::fromString("#FFFFFFFF"));
		setColour(postColour,  juce::Colour::fromString("#FFFF97F5"));
		setColour(bandColour1, juce::Colour::fromString("#FFFFFF69"));
		setColour(bandColour2, juce::Colour::fromString("#FF93E5FF"));
		setColour(bandColour3, juce::Colour::fromString("#FF96FF94"));
		setColour(bandColour4, juce::Colour::fromString("#FFFF9B63"));
		setColour(bandColour5, juce::Colour::fromString("#FF5EFFBB"));

		//transient splitting
		setColour(transientColour,	findColour(bandColour4));
		setColour(sustainColour, findColour(bandColour5));

		//buttons
		setColour(buttonDownColour,			findColour(bright));
		setColour(buttonUpColour,			findColour(mediumGrey).withAlpha(0.4f));
		setColour(buttonBackgroundColour,	juce::Colours::transparentBlack);

		//Label
		setColour(juce::Label::ColourIds::backgroundWhenEditingColourId, juce::Colours::transparentBlack);

		//popups
		setColour(juce::BubbleComponent::outlineColourId,		findColour(bright));
		setColour(juce::BubbleComponent::backgroundColourId,	findColour(mediumDarkGrey));

		setColour(juce::PopupMenu::backgroundColourId,				findColour(mediumDarkGrey).withAlpha(0.99f));
		setColour(juce::PopupMenu::highlightedBackgroundColourId,	juce::Colours::transparentBlack);
		setColour(juce::PopupMenu::textColourId,					findColour(mediumGrey));
		setColour(juce::PopupMenu::highlightedTextColourId,			juce::Colours::white);

		//sliders
		setColour(juce::Slider::rotarySliderFillColourId,		findColour(mediumDarkGrey));	//colour of the filled progressbar - bright green
		setColour(juce::Slider::rotarySliderOutlineColourId,	juce::Colours::transparentBlack);		//colour of the unfilled progressbar - tranparent
		setColour(juce::Slider::thumbColourId,					juce::Colours::white);								//colour of the unfilled progressbar - tranparent
		setColour(juce::Slider::backgroundColourId,				findColour(mediumDarkGrey));
		setColour(juce::Slider::ColourIds::trackColourId,		juce::Colours::white.withAlpha(0.2f));

		//other Comps
		setColour(envelopeAnalyzerFillColour, juce::Colours::white);

		setColour(juce::CaretComponent::caretColourId, juce::Colours::white);

		setColour(juce::TextEditor::highlightColourId, juce::Colours::white);
		setColour(juce::TextEditor::highlightedTextColourId, findColour(darkGrey));

		setDefaultSansSerifTypeface(getNotoSans());

		//Dynamic chain colours
		setColour(nodeBGColour, juce::Colour::fromString("#FF2B2B2B"));

		gainColourGradient = juce::ColourGradient::vertical(
			juce::Colour::fromString("#FFDAFFE9"), 0.0f,
			juce::Colour::fromString("#FFFFDADA"), 1.0f
		);
		gainColourGradient.addColour(0.5f, juce::Colour::fromString("#FFFFF5DA"));
	}

	static const juce::Typeface::Ptr getNotoSans(bool isBold = false, bool isItalic = false)
	{
		static auto normalTypeface = juce::Typeface::createSystemTypefaceFor(
			Suritz::NotoSansFont::NotoSansRegular_ttf,
			Suritz::NotoSansFont::NotoSansRegular_ttfSize);

		static auto boldTypeface = juce::Typeface::createSystemTypefaceFor(
			Suritz::NotoSansFont::NotoSansBold_ttf,
			Suritz::NotoSansFont::NotoSansBold_ttfSize);

		if (isBold && !isItalic)
			return boldTypeface;

		return normalTypeface;
	}

	static juce::Font getFont (FontSizes size, bool isBold = false, bool isItalic = false)
    {
        auto font = juce::Font (getNotoSans (isBold, isItalic));
        font = font.withPointHeight (size);
        return font;
    }

	juce::Typeface::Ptr getTypefaceForFont(const juce::Font& font) override
	{
		if (font.isBold())
			return getNotoSans(true);

		return getNotoSans();
	}

	static float getPopupMenuFontHeight() {	return 20.f; }
	static float getToolTipFontHeight() { return getPopupMenuFontHeight(); }
	static int getToolTipBorder() { return 10; }

	void drawTooltip(juce::Graphics& g, const juce::String& text, int width, int height) override
	{
		auto bounds = juce::Rectangle<int>(0, 0, width, height);
		drawPopupMenuBackground(g, width, height);
		bounds.reduce(6, 0);

		//setFontPoints(g, getToolTipFontHeightPoints());
		g.setFont(getToolTipFontHeight());
		g.setColour(juce::Colours::white);
		g.drawFittedText(text, bounds.reduced(getToolTipBorder()), juce::Justification::centredLeft, 10, 1.f);
	}
	
	static juce::TextLayout layoutTooltipText(const juce::String& text, juce::Colour colour) noexcept
	{
		const int maxToolTipWidth = 250;

		juce::AttributedString s;
		s.setJustification(juce::Justification::centredLeft);
		//s.append(text, juce::Font(10.f, juce::Font::plain).withPointHeight(getToolTipFontHeightPoints()), colour);
		s.append(text, juce::Font(getToolTipFontHeight(), juce::Font::plain), colour);
		
		juce::TextLayout tl;
		tl.createLayoutWithBalancedLineLengths(s, (float)maxToolTipWidth);
		return tl;
	}

	juce::Rectangle<int> getTooltipBounds
        (const juce::String& tipText,
		juce::Point<int> screenPos,
		juce::Rectangle<int> parentArea) override
	{
		const juce::TextLayout tl(layoutTooltipText(tipText, juce::Colours::black));

		auto w = (int)(tl.getWidth() + 26.0f);
        auto h = (int) (tl.getHeight() + 26.0f);

		return juce::Rectangle<int>(
			screenPos.x > parentArea.getCentreX() ? screenPos.x - (w + 12) : screenPos.x + 24,
			screenPos.y > parentArea.getCentreY() ? screenPos.y - (h + 6) : screenPos.y + 6,
			w, 
			h).constrainedWithin(parentArea).expanded(getToolTipBorder());
	}

	static juce::Rectangle<int> getDefaultButtonBounds(bool largeVersion = false)
	{
		return juce::Rectangle<int>(0, 0, 137, 32);
	}

	static LookAndFeel& getInstance()
	{
		static LookAndFeel instance;
		return instance;
	}

	static int getChainNodeBackgroundBorder() 
	{
		return 5;
	}

	static void paintChainNodeBackground(juce::Graphics& g, juce::Rectangle<float> bounds,
		juce::Colour strokeTop, juce::Component& compWithLAF, float lineThickness = 1.f, bool dashedStroke = false, juce::Colour bgTop = juce::Colours::transparentBlack)
	{
		bounds.reduce(1.f, 1.f);
		juce::Image img(juce::Image::PixelFormat::ARGB, compWithLAF.getWidth(), compWithLAF.getHeight(), true);
		juce::Graphics gr(img);

		//bounds = bounds.reduced(getChainNodeBackgroundBorder() + 1);
		const float cornerSize = 17.f;
		if(bgTop == juce::Colours::transparentBlack)
			bgTop = compWithLAF.findColour(nodeBGColour);
		const auto bot = compWithLAF.findColour(darkGrey);
		gr.setGradientFill(juce::ColourGradient::vertical(bgTop, bot, bounds));
		gr.fillRoundedRectangle(bounds, cornerSize);

		auto gradient = juce::ColourGradient::vertical(strokeTop, bot, bounds);
		gradient.addColour(0.9, bot);
		gr.setGradientFill(gradient);
		if (dashedStroke)
		{
			juce::Path path;
			path.addRoundedRectangle(bounds, cornerSize);
			juce::PathStrokeType stroke(lineThickness);
			std::array<float, 2> dashes{ 4.f, 4.f };
			stroke.createDashedStroke(path, path, dashes.data(), 2);
			gr.fillPath(path);
		}
		else
			gr.drawRoundedRectangle(bounds, cornerSize, lineThickness);

		LookAndFeel::drawLightShadow(g, img);
		g.drawImageAt(img, 0, 0);
	}

	void paintFocusedWindowBackground(juce::Graphics& g, juce::Rectangle<int> bounds)
	{
		auto c = findColour(darkGrey);
		g.fillAll(c.withAlpha(0.95f));
	}

	static juce::ColourGradient getSliderFillGradient()
	{
		juce::ColourGradient gradient;
		gradient.addColour(0.0, juce::Colour::fromString("#FF2B2B2B"));
		gradient.addColour(1.0, juce::Colour::fromString("#FF1A1A1A"));
		return gradient;
	}

	static void drawInnerShadow(juce::Graphics& g, juce::Path& target, juce::DropShadow& shadow)
	{
		// resets the Clip Region when the function returns
		juce::Graphics::ScopedSaveState saveState(g);

		// invert the path's fill shape and enlarge it,
		// so it casts a shadow
		juce::Path shadowPath(target);
		shadowPath.addRectangle(target.getBounds().expanded(10));
		shadowPath.setUsingNonZeroWinding(false);

		// reduce clip region to avoid the shadow
		// being drawn outside of the shape to cast the shadow on
		g.reduceClipRegion(target);

		shadow.drawForPath(g, shadowPath);
	}

	juce::Font getPopupMenuFont() override
	{
		return juce::Font(22.f);
	}

	static void drawSplitRegionBorder(juce::Graphics& g, juce::Rectangle<int> rect, juce::Colour c)
	{
		const auto w = rect.getWidth(), h = rect.getHeight();
		const auto thickness = 1.f;
		g.setColour(c);
		juce::Path border;

		border.startNewSubPath(thickness, h - thickness);
		border.lineTo(thickness, thickness);
		border.lineTo(w - thickness, thickness);
		border.lineTo(w - thickness, h - thickness);

		const auto roundedBorder = border.createPathWithRoundedCorners(15.f);
		const auto strokeType = juce::PathStrokeType(3.f, juce::PathStrokeType::curved);
		g.strokePath(roundedBorder, strokeType);
	}

	void drawComboBox(juce::Graphics& g, int width, int height,
		bool isButtonDown, int buttonX, int buttonY, int buttonW, int buttonH, juce::ComboBox& c) override
	{
	}

	void positionComboBoxText(juce::ComboBox& c, juce::Label& labelToPosition) override
	{
		labelToPosition.setBounds(c.getLocalBounds());
	}

	void drawPopupMenuBackground(juce::Graphics& g, int w, int h) override
	{
		drawPopupBackground(g, { 0.f, 0.f, float(w), float(h) }, 0.f);
	}

	bool shouldPopupMenuScaleWithTargetComponent(const juce::PopupMenu::Options& options) override
	{
		return true;
	}

	juce::Font getSliderPopupFont(juce::Slider& slider) override
	{
		return juce::Font(25.f, juce::Font::FontStyleFlags::plain).withPointHeight(16.f);
	}

	int getSliderPopupPlacement(juce::Slider& slider) override
	{
		return /*juce::BubbleComponent::above + */juce::BubbleComponent::below;
	}

	void drawBubble(juce::Graphics& g, juce::BubbleComponent& bubbleComp, 
		const juce::Point<float>& positionOfTip, const juce::Rectangle<float>& body) override
	{
		drawPopupBackground(g, body);
	}

	void drawAlertBox(juce::Graphics& g, juce::AlertWindow& window, 
		const juce::Rectangle< int >& textArea, juce::TextLayout& layout) override
	{
		auto bounds = window.getLocalBounds().toFloat();

		g.setColour(findColour(darkGrey));
		g.fillRect(bounds);

		g.setColour(juce::Colours::white);
		g.drawRect(bounds);

		layout.draw(g, bounds.reduced(50));
	}

	/*
	general popup bg drawing. Used for bubblecomp and popup menu
	*/
	void drawPopupBackground(juce::Graphics& g, juce::Rectangle<float> area, float cornerSize = 7.f)
	{
		juce::Path path;
		if (cornerSize > 0.f)
			path.addRoundedRectangle(area, cornerSize);
		else
			path.addRectangle(area);

		g.setColour(findColour(juce::BubbleComponent::backgroundColourId));
		g.fillPath(path);

		//g.setColour(findColour(juce::BubbleComponent::outlineColourId).withAlpha(0.75f));
		g.strokePath(path, juce::PathStrokeType(1.f));
	}
		
	static void drawDropdowArrow(juce::Graphics& g, juce::Point<float> centre, 
		bool isMouseOver, float radius = 6.5f, float mouseOverRadAdd = 1.f)
	{
		juce::Path arrowPath;
		const auto rad = isMouseOver ? radius + mouseOverRadAdd : radius;
		arrowPath.addPolygon(centre, 3, rad, juce::MathConstants<float>::pi);
		arrowPath = arrowPath.createPathWithRoundedCorners(3.f);
		g.fillPath(arrowPath);
	}

	static juce::DropShadow getTextShadow()
	{
		static juce::DropShadow shadow{juce::Colour::fromString("#FF141414"), 9, {0, 0}};
		return shadow;
	}

	static int lightShadowExpand() 
	{
		return 10;
	}

	static juce::DropShadow getLightShadow()
	{
		static juce::DropShadow lightShadow{ juce::Colour::fromString("#FF0D0D0D"), 8, {0, 0}};
		return lightShadow;
	}

	void paintSimpleWidgetBackground(
		juce::Graphics& g, juce::Rectangle<float> rect, 
		bool drawBright, bool drawThick, 
		bool fill = true, bool stroke = true)
	{
		rect = rect.reduced(2.f);
		const auto cornerSize = 5.f;

		if (fill)
		{
			g.setColour(findColour(darkGrey));
			g.fillRoundedRectangle(rect, cornerSize);
		}

		if (stroke)
		{
			g.setColour(drawBright ? juce::Colours::white : findColour(semiDarkGrey));
			g.drawRoundedRectangle(rect, cornerSize, drawThick ? 2.f : 1.f);
		}
	}

	void paintErrorWidgetBackground(
		juce::Graphics& g, juce::Rectangle<float> rect, 
		bool drawBright, bool drawThick, 
		bool fill = true, bool stroke = true)
	{
		rect = rect.reduced(2.f);
		const auto cornerSize = 5.f;

		if (fill)
		{
			g.setColour(findColour(darkGrey));
			g.fillRoundedRectangle(rect, cornerSize);
		}

		if (stroke)
		{
			auto c = findColour(warning);
			g.setColour(drawBright ? c : c.withAlpha(0.4f));
			g.drawRoundedRectangle(rect, cornerSize, drawThick ? 2.f : 1.f);
		}
	}
	
	void fillTextEditorBackground(juce::Graphics& g, int width, int height, juce::TextEditor& editor) override
	{
		auto bounds = editor.getLocalBounds().toFloat();
		paintSimpleWidgetBackground(g, bounds, shouldDrawFocusedEditor(editor), false, true, false);
	}

	static bool shouldDrawFocusedEditor(juce::TextEditor& textEditor)
	{
		if (dynamic_cast<juce::AlertWindow*> (textEditor.getParentComponent()) == nullptr)
			if (textEditor.isEnabled())
				if (textEditor.hasKeyboardFocus(true) && !textEditor.isReadOnly())
					return true;

		if (textEditor.isMouseOver(true))
			return true;

		return false;
	}

	void drawTextEditorOutline(juce::Graphics& g, int width, int height, juce::TextEditor& editor) override
	{
		auto bounds = editor.getLocalBounds().toFloat().reduced(1.f);
		paintSimpleWidgetBackground(g, bounds, shouldDrawFocusedEditor(editor), false, false, true);
	}

	/**
	* maybe bad performance since creating shadow obj
	*/
	static void drawTextShadow(juce::Graphics& g, juce::Image& img)
	{
		getTextShadow().drawForImage(g, img);
	}
	static void drawLightShadow(juce::Graphics& g, juce::Image& img)
	{
		getLightShadow().drawForImage(g, img);
	}

	static void dbgBounds(juce::Graphics& g, juce::Rectangle<int> area, juce::Colour c = juce::Colours::red)
	{
#if DBG_BOUNDS

		juce::Graphics::ScopedSaveState save(g);
		g.setColour(c);
		g.drawRect(area);

#endif
	}

	static constexpr float ARROW_RAD_L = 7.5f, ARROW_RAD_S = 6.5f; 
	static constexpr int ARROW_WIDTH = 23;

private:
	juce::DropShadow textDropShadow{ getTextShadow() };
	juce::ColourGradient gainColourGradient;
};

struct SeperatorLine :
	public juce::Component
{
	SeperatorLine()
	{
		setInterceptsMouseClicks(false, false);
		setComponentEffect(&dropShadow);
		dropShadow.setShadowProperties({ juce::Colours::black.withAlpha(1.f), 10, {4, 4 } });
	}

	void paint(juce::Graphics& g) override
	{
		g.setColour(getLookAndFeel().findColour(LookAndFeel::lineColour));
		g.drawLine(line, 1.f);
	}

	void resized() override
	{
	}

	void setLine(juce::Line<int> newLine)
	{
		line = newLine.toFloat();

		setBounds(getParentComponent()->getLocalBounds()); //adjust component to size of parent for dropshadow
		repaint();
	}

private:
	juce::Line<float> line;
	juce::DropShadowEffect dropShadow;
};

struct RoundButton :
	juce::Button
{
	static constexpr int DEF_BUTTON_WIDTH = 32;
	static constexpr int DEF_BUTTON_HEIGHT = DEF_BUTTON_WIDTH;
	static constexpr float DEF_BUTTON_FONTSIZE = 15.f;

	enum
	{
		onColour = 15353246,
		offColour = 561646,
		bgColour = 6436634,
	};

	RoundButton() :
		juce::Button("roundButton")
	{
		setClickingTogglesState(true);

		setColour(onColour, findColour(LookAndFeel::bright));
		setColour(offColour, findColour(LookAndFeel::mediumGrey));
		setColour(bgColour, findColour(LookAndFeel::darkGrey));
	}

	void resized() override
	{

	}

	void paintButton(juce::Graphics& g, bool buttonHighlighted, bool buttonDown) override
	{
		auto area = getLocalBounds().toFloat();
		const bool state = getToggleState();

		g.setColour(state ? findColour(onColour) : findColour(offColour).withAlpha(0.4f));
		g.fillEllipse(area);

		g.setColour(findColour(bgColour));
		g.fillEllipse(area.reduced(buttonHighlighted ? 1.5f : 1.f));
	}

	void mouseMove(const juce::MouseEvent& e) override
	{
		juce::Button::mouseMove(e);

		//getParentComponent()->mouseMove(e);
	}
};

struct CloseButton : public Suritz::RoundButton
{
    CloseButton()
    {
        auto warningC = findColour (LookAndFeel::warning);
        setColour (RoundButton::onColour, warningC);
        setColour (RoundButton::offColour, warningC);
	}
    
	void paintButton (juce::Graphics& g, bool highlighted, bool is_On) override
    {
        auto area = getLocalBounds().toFloat();

        g.setColour (findColour (offColour));
        g.fillEllipse (area);

        g.setColour (findColour (bgColour));
        g.fillEllipse (area.reduced (highlighted ? 1.5f : 1.f));

        g.setColour (findColour (offColour));
        Suritz::setFontPoints (g, RoundButton::DEF_BUTTON_FONTSIZE);
        g.drawText ("X", getLocalBounds(), juce::Justification::centred, false);
    }
};

struct DeleteButton : public Suritz::RoundButton
{
    DeleteButton()
    {
        auto warningC = findColour (LookAndFeel::warning);
        setColour (RoundButton::onColour, warningC);
        setColour (RoundButton::offColour, warningC);
	}
    
	void paintButton (juce::Graphics& g, bool highlighted, bool is_On) override
    {
        RoundButton::paintButton (g, highlighted, is_On);

        g.setColour (findColour (offColour));
        Suritz::setFontPoints (g, RoundButton::DEF_BUTTON_FONTSIZE);
        g.drawText ("X", getLocalBounds(), juce::Justification::centred, false);
    }
};

struct ToggleTextButton :
	public juce::Button
{
	ToggleTextButton() :
		juce::Button(juce::String())
	{
		setBufferedToImage(true);
	}

	virtual void paintButton(juce::Graphics& g,
		bool shouldDrawButtonAsHighlighted,
		bool shouldDrawButtonAsDown) override
	{
		juce::Image img(juce::Image::ARGB, getWidth(), getHeight(), true);
		juce::Graphics gr(img);
		auto fontSizeP = isMouseOverOrDragging() ? fontSize + fontSizeAdd : fontSize;
		gr.setFont(gr.getCurrentFont().withPointHeight(fontSizeP));
		gr.setColour(getToggleState() ?
			findColour(Suritz::LookAndFeel::buttonDownColour) :
			findColour(Suritz::LookAndFeel::buttonUpColour));
		gr.drawFittedText(getButtonText(), getLocalBounds(), textJustification, numTextLines);
		Suritz::LookAndFeel::drawTextShadow(g, img);

		g.drawImageAt(img, 0, 0);

		Suritz::LookAndFeel::dbgBounds(g, getLocalBounds());
	}

	float fontSize = 20.f;
	float fontSizeAdd = 1.f;
	int numTextLines = 1;
	juce::Justification textJustification{ juce::Justification::centred };
};

struct TextButton :
	public juce::Button
{
	TextButton() :
		juce::Button(juce::String())
	{
		setBufferedToImage(true);
	}

	virtual void paintButton(juce::Graphics& g,
		bool shouldDrawButtonAsHighlighted,
		bool shouldDrawButtonAsDown) override
	{
		juce::Image img(juce::Image::ARGB, getWidth(), getHeight(), true);
		juce::Graphics gr(img);
		Suritz::setFontPoints(gr, fontSize);
		gr.setColour(isMouseOver() ?
			findColour(Suritz::LookAndFeel::buttonDownColour) :
			findColour(Suritz::LookAndFeel::buttonUpColour));
		gr.drawFittedText(getButtonText(), getLocalBounds(), textJustification, numTextLines);
		Suritz::LookAndFeel::drawTextShadow(g, img);

		g.drawImageAt(img, 0, 0);

		Suritz::LookAndFeel::dbgBounds(g, getLocalBounds());
	}

	float fontSize = 20.f;
	int numTextLines = 1;
	juce::Justification textJustification{ juce::Justification::centred };
};

struct TextComboBox :
	public juce::ComboBox
{
	TextComboBox()
	{
		setScrollWheelEnabled(true);
		setBufferedToImage(true);

		onChange = [this]() {/*mouseOver = false;*/ };
	}

	void resized() override {}

	void paint(juce::Graphics& g) override
	{
		juce::Image img(juce::Image::PixelFormat::ARGB, getWidth(), getHeight(), true);
		juce::Graphics gr(img);
		const auto bounds = getLocalBounds();
		const auto text = getText();

		auto fontSizeP = isMouseOverOrDragging() ? fontSize + mouseOverFontSizeAdd : fontSize;
		gr.setFont(gr.getCurrentFont().withPointHeight(fontSizeP));
		gr.setColour(findColour(juce::ComboBox::textColourId));
		gr.drawFittedText(getText(), getLocalBounds(), textJustification, 1, 0.5f);

		if (drawArrow)
		{
			const auto strW = gr.getCurrentFont().getStringWidthFloat(text);
			const auto arrowR = juce::roundToInt(getWidth() / 2 - strW / 2.f);
			const auto arrowB = bounds.withRight(arrowR);
			Suritz::LookAndFeel::drawDropdowArrow(gr, arrowB.toFloat().getCentre(), isMouseOverOrDragging(), arrowRadius);
		}

		Suritz::LookAndFeel::drawTextShadow(g, img);
		g.drawImageAt(img, 0, 0);

		Suritz::LookAndFeel::dbgBounds(g, getLocalBounds());
	}

	static constexpr float DEF_COMBO_FONTSIZE_P = 20.f;

	void setArrow(bool shouldDrawArrow, float newArrowRadius = 0.f)
	{
		drawArrow = shouldDrawArrow;
		arrowRadius = newArrowRadius;
	}

	void setFont(float newFontSize, float fontSizeAdd = 1.f, juce::Justification justification = juce::Justification::centred)
	{
		fontSize = newFontSize;
		mouseOverFontSizeAdd = fontSizeAdd;
		textJustification = justification;
	}
	
	void nudgeSelectedItem(int delta)
	{
		const auto current = getSelectedItemIndex();
		const auto target = current+ delta;
		
		if (target > -1 && target < getNumItems())
		{
			setSelectedItemIndex(target, juce::NotificationType::sendNotification);
			return;
		}
		//jassertfalse;
	}

	void mouseWheelMove(const juce::MouseEvent& e, const juce::MouseWheelDetails& wheel) override
	{
		if (!isPopupActive()  && e.eventComponent == this && wheel.deltaY != 0.0f)
		{
			if (wheel.isSmooth)
			{
				mouseWheelAccumulator += wheel.deltaY * 5.0f;

				while (mouseWheelAccumulator > 1.0f)
				{
					mouseWheelAccumulator -= 1.0f;
					nudgeSelectedItem(-1);
				}

				while (mouseWheelAccumulator < -1.0f)
				{
					mouseWheelAccumulator += 1.0f;
					nudgeSelectedItem(1);
				}
			}
			else
			{
				auto delta = wheel.isReversed ? wheel.deltaY : -1.f * wheel.deltaY;
				if (delta > 0)
					nudgeSelectedItem(1);
				else
					nudgeSelectedItem(-1);
			}
		}
		else
		{
			Component::mouseWheelMove(e, wheel);
		}
	}

private:
	float mouseWheelAccumulator = 0.f;

	float arrowRadius = 6.5f;
	bool drawArrow = true;

	float fontSize = DEF_COMBO_FONTSIZE_P;
	float mouseOverFontSizeAdd = 1.f;
	juce::Justification textJustification{ juce::Justification::centred };
};

struct AttachedTextComboBox :
	public TextComboBox
{
	AttachedTextComboBox(APVTS& state, const juce::String& paramID, const juce::StringArray& items)
	{
		addItemList(items, 1);

		attach = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>
			(state, paramID, *this);
	}

private:
	std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> attach;
};

struct TooltipWindowWithShadow :
	public juce::TooltipWindow
{
	TooltipWindowWithShadow() :
		juce::TooltipWindow(nullptr, 1000)
	{
		setOpaque(true);
		shadow.setOwner(this);
	}
	
	juce::DropShadower shadow{ juce::DropShadow(juce::Colours::black.withAlpha(0.8f), 10, {0,0})};
};

struct ButtonOutline : 
	public juce::Button
{
	enum ColourIDs
	{
		NormalOutline,
		OverOutline,
		Background
	};

	ButtonOutline() :
		juce::Button("")
	{
		setBufferedToImage(true);

		setColour(Background, findColour(Suritz::LookAndFeel::darkGrey));
		setColour(juce::TextButton::textColourOnId, findColour(Suritz::LookAndFeel::bright));
		setColour(NormalOutline, findColour(Suritz::LookAndFeel::semiDarkGrey));
		setColour(OverOutline, findColour(Suritz::LookAndFeel::bright));
	}

	void paintButton(juce::Graphics& g, bool isOver, bool isDown)
	{
		auto rect = getLocalBounds().toFloat().reduced(2.f);
		const auto cornerSize = 5.f;
		const auto outlineC = isClickable && isOver ? findColour(OverOutline) : findColour(NormalOutline);

		g.setColour(findColour(Background));
		g.fillRoundedRectangle(rect, cornerSize);

		g.setColour(outlineC);
		if (!isClickable)
		{
			juce::Path path;
			path.addRoundedRectangle(rect, 5.f);
			g.strokePath(path, juce::PathStrokeType(strokeThicknessNormal));
		}
		else
			g.drawRoundedRectangle(rect, cornerSize, isDown ? strokeThicknessOver : strokeThicknessNormal);
		
		Suritz::setFontPoints(g, 16.f);
		g.setColour(findColour(juce::TextButton::textColourOnId));
		g.drawFittedText(getButtonText(), getLocalBounds(), juce::Justification::centred, 2);
	}

	bool getClickable() { return isClickable; }
	void setClickable(bool shouldBeClickable) { isClickable = shouldBeClickable; }
	void setStrokeThickness(const float normal = 1.f, const float over = 2.f)
	{
		strokeThicknessNormal = normal;
		strokeThicknessOver = over;
	}
	//returns normal strokethickness when ThicknessWhenOver = false and over strokethickness when ThicknessWhenOver = true
	float getStrokeThickness(bool ThicknessWhenOver) 
	{
		return ThicknessWhenOver ? strokeThicknessOver : strokeThicknessNormal;
	}
private:
	float strokeThicknessNormal = 1.f;
	float strokeThicknessOver = 2.f;
	bool isClickable = true;
};

struct ButtonOutlineRed :
	public ButtonOutline
{
public:
	ButtonOutlineRed()
	{
		const auto red = findColour(Suritz::LookAndFeel::warning);
		setColour(Suritz::ButtonOutline::OverOutline, red);
		setColour(juce::TextButton::textColourOnId, red);
		setColour(Suritz::ButtonOutline::NormalOutline, findColour(Suritz::LookAndFeel::warningDark));
	}
private:

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ButtonOutlineRed)
};

struct ButtonNoOutline :
	public juce::Button,
	private juce::Timer
{
	static constexpr int CORNERSIZE = 8;
	static constexpr float LINEWIDTH = 1.5f;

	ButtonNoOutline() :
		juce::Button({})
	{
		setBufferedToImage(true);

		smoothOutlineOpacity.setCurrentAndTargetValue(0.f);
		smoothOutlineOpacity.reset(10);
	}

	void mouseEnter(const juce::MouseEvent& e) override
	{
		juce::Button::mouseEnter(e);
		smoothOutlineOpacity.setTargetValue(1.f);
		startTimerHz(30);
	}
	void mouseExit(const juce::MouseEvent& e) override
	{
		juce::Button::mouseExit(e);
		mouseExitFadeout();
	}
	void mouseExitFadeout()
	{
		smoothOutlineOpacity.setTargetValue(0.f);
		startTimerHz(30);
	}

	virtual void paint(juce::Graphics& g) override
	{
		auto b = getLocalBounds().reduced(1).toFloat();

		g.setColour(findColour(Suritz::LookAndFeel::darkGrey));
		g.fillRoundedRectangle(b, CORNERSIZE);

		auto opacity = smoothOutlineOpacity.getCurrentValue();
		g.setColour(findColour(Suritz::LookAndFeel::bright).withAlpha(opacity));
		g.drawRoundedRectangle(b, CORNERSIZE, LINEWIDTH);

		paintButton(g, isOver(), isDown());
		
		Suritz::LookAndFeel::dbgBounds(g, getLocalBounds(), juce::Colours::yellow);
	}

	void timerCallback() override
	{
		smoothOutlineOpacity.getNextValue();
		repaint();

		auto val = smoothOutlineOpacity.getCurrentValue();

		if (val == 1.f || val == 0.f)
			stopTimer();
	}
private:
	juce::SmoothedValue<float> smoothOutlineOpacity;
};

/**
* ButtonNoOutline child for quick image integration
*/
struct ImageSOButton :
	public ButtonNoOutline
{
	void paintButton(juce::Graphics& g, bool drawHighlight, bool drawDown) override
	{
		jassert(img.isValid()); //you need to set the image first

		const auto w = getWidth(), h = getHeight();
		const auto iw = img.getWidth(), ih = img.getHeight();
		g.setColour(findColour(Suritz::LookAndFeel::textColour));
		g.drawImageAt(img, w / 2 - iw / 2, h / 2 - ih / 2);
	}

	juce::Image img;
};

struct LockButton :
	public ButtonNoOutline
{
	LockButton()
	{
		setClickingTogglesState(true);
	}

	void paintButton(juce::Graphics& g, bool isOver, bool isDown)
	{
		auto& img = getToggleState() ? down : up;

		const auto w = getWidth(), h = getHeight();
		const auto iw = img.getWidth(), ih = img.getHeight();
		g.setColour(findColour(Suritz::LookAndFeel::textColour));
		g.drawImageAt(img, w / 2 - iw / 2, h / 2 - ih / 2);
	}

	juce::Image down = juce::ImageFileFormat::loadFrom(Ressources::saveButton_locked_png,   Ressources::saveButton_locked_pngSize);
	juce::Image up   = juce::ImageFileFormat::loadFrom(Ressources::saveButton_unlocked_png, Ressources::saveButton_unlocked_pngSize);
};

struct TextEditor :
	public juce::TextEditor
{
	TextEditor()
	{
		setFont(getFont().withPointHeight(16.f));
		setJustification(juce::Justification::centred);
		onEscapeKey = [this]() {unfocusAllComponents(); };
	}
};

struct CloseableWindowComponent:
	public juce::Component,
	public juce::Timer
{
	CloseableWindowComponent()
	{
		smClose.reset(10);
		smClose.setCurrentAndTargetValue(1.f);
	}

	void timerCallback() override
	{
		const auto val = smClose.getNextValue();
		repaint();

		/*for (auto& child : getChildren())
			child->setAlpha(val);*/

		if (val == 0.f)
			close();
	}

	//use paintContent instead of overriding this
	void paint(juce::Graphics& g) final override
	{
		const auto c = findColour(LookAndFeel::darkGrey);
		const auto val = smClose.getCurrentValue();

		setAlpha(val);

		auto gradient = juce::ColourGradient::vertical(c.withAlpha(0.6f), c, getLocalBounds().withHeight(getHeight() / 2));
		g.setGradientFill(gradient);
		g.fillAll();

		paintContent(g);
	}

	virtual void paintContent(juce::Graphics& g) 
	{
	}

	void startClosing()
	{
		startTimerHz(30);
		smClose.setCurrentAndTargetValue(1.f);
		smClose.setTargetValue(0.f);
	}

	/**
	* used internally to finish closing process, 
	* can always be called to force closing
	*/
	void close()
	{
		stopTimer();
		setVisible(false);

		setAlpha(1.f);
		smClose.setCurrentAndTargetValue(1.f);
	}

private:
	juce::SmoothedValue<float> smClose;
};
