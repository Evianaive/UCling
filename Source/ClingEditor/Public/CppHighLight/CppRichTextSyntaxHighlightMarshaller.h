﻿// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once

#include "CodeEditorStyle.h"
#include "SyntaxTextStyle.h"
#include "Framework/Text/SyntaxHighlighterTextLayoutMarshaller.h"

class FTextLayout;

/**
 * Get/set the raw text to/from a text layout, and also inject syntax highlighting for our rich-text markup
 */
class CLINGEDITOR_API FCppRichTextSyntaxHighlightMarshaller : public FSyntaxHighlighterTextLayoutMarshaller
{
public:

	static TSharedRef< FCppRichTextSyntaxHighlightMarshaller > Create(const FSyntaxTextStyle& InSyntaxTextStyle);

	virtual ~FCppRichTextSyntaxHighlightMarshaller();

protected:

	virtual void ParseTokens(const FString& SourceString, FTextLayout& TargetTextLayout, TArray<ISyntaxTokenizer::FTokenizedLine> TokenizedLines) override;

	FCppRichTextSyntaxHighlightMarshaller(TSharedPtr< ISyntaxTokenizer > InTokenizer, const FSyntaxTextStyle& InSyntaxTextStyle);

	/** Styles used to display the text */
	const FSyntaxTextStyle& SyntaxTextStyle;

	/** String representing tabs */
	FString TabString;
};
