#ifndef __UILABEL_H__
#define __UILABEL_H__

#pragma once
#include <gdiplus.h>
using namespace Gdiplus;
class UILIB_API Gdiplus::RectF;

namespace DuiLib
{
	class UILIB_API CLabelUI : public CControlUI
	{
	public:
		CLabelUI();
		~CLabelUI();

		LPCTSTR GetClass() const;
		LPVOID GetInterface(LPCTSTR pstrName);

		void SetTextStyle(UINT uStyle);
		UINT GetTextStyle() const;
		void SetTextColor(DWORD dwTextColor);
		DWORD GetTextColor() const;
		void SetDisabledTextColor(DWORD dwTextColor);
		DWORD GetDisabledTextColor() const;
		void SetFont(int index);
		int GetFont() const;
		RECT GetTextPadding() const;
		void SetTextPadding(RECT rc);
		bool IsShowHtml();
		void SetShowHtml(bool bShowHtml = true);
		bool		IsAutoCalcWidth();
		void		SetAutoCalcWidth(bool bautoCalcWidth);

		SIZE EstimateSize(SIZE szAvailable);
		void DoEvent(TEventUI& event);
		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

		void PaintText(HDC hDC);

		void		SetEnabledEffect(bool _EnabledEffect);
		bool		GetEnabledEffect();
		void		SetTransShadow(int _TransShadow);
		int			GetTransShadow();
		void		SetTransShadow1(int _TransShadow);
		int			GetTransShadow1();
		void		SetTransText(int _TransText);
		int			GetTransText();
		void		SetTransText1(int _TransText);
		int			GetTransText1();
		void		SetTransStroke(int _TransStroke);
		int			GetTransStroke();
		void		SetGradientLength(int _GradientLength);
		int			GetGradientLength();
		void		SetTextRenderingHintAntiAlias(int _TextRenderingHintAntiAlias);
		int			GetTextRenderingHintAntiAlias();
		void		SetShadowOffset(int _offset,int _angle);
		Gdiplus::RectF		GetShadowOffset();
		void		SetTextColor1(DWORD _TextColor1);
		DWORD		GetTextColor1();
		void		SetTextShadowColorA(DWORD _TextShadowColorA);
		DWORD		GetTextShadowColorA();
		void		SetTextShadowColorB(DWORD _TextShadowColorB);
		DWORD		GetTextShadowColorB();
		void		SetStrokeColor(DWORD _StrokeColor);
		DWORD		GetStrokeColor();
		void		SetGradientAngle(int _SetGradientAngle);
		int			GetGradientAngle();
		void		SetEnabledStroke(bool _EnabledStroke);
		bool		GetEnabledStroke();
		void		SetEnabledShadow(bool _EnabledShadowe);
		bool		GetEnabledShadow();

		void        SetText(LPCTSTR pstrText) override;

	protected:
		DWORD	m_dwTextColor;
		DWORD	m_dwDisabledTextColor;
		int		m_iFont;
		UINT	m_uTextStyle;
		RECT	m_rcTextPadding;
		bool	m_bShowHtml;
		bool					m_AutoCalcWidth;

		int						m_hAlign;
		int						m_vAlign;
		int						m_TransShadow;
		int						m_TransShadow1;
		int						m_TransText;
		int						m_TransText1;
		int						m_TransStroke;
		int						m_GradientLength;
		int						m_GradientAngle;
		bool					m_EnableEffect;
		bool					m_EnabledStroke;
		bool					m_EnabledShadow;
		DWORD					m_dwTextColor1;
		DWORD					m_dwTextShadowColorA;
		DWORD					m_dwTextShadowColorB;
		DWORD					m_dwStrokeColor;
		Gdiplus::RectF			m_ShadowOffset;
		//		CDuiString				m_TextValue; //��Ч��,����
		TextRenderingHint		m_TextRenderingHintAntiAlias;
	};
}

#endif // __UILABEL_H__