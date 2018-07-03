#pragma once

namespace DuiLib
{
	class UILIB_API CProgressPieUI :
		public CLabelUI
	{
	public:
		CProgressPieUI();
		~CProgressPieUI();

		virtual LPCTSTR GetClass() const;
		virtual LPVOID GetInterface(LPCTSTR pstrName);
		virtual void DoEvent(TEventUI& event);
		virtual void DoPaint(HDC hDC, const RECT& rcPaint);
		
		void SetProgress(float nscala);
		float GetProgress();
	private:
		void PaintProgessPie(HDC hDC, const RECT& rcPaint);
		
	private:
		float m_fSweepAngel = -120;	//需要绘制的弧度值，应该为 0-360度范围；
		float m_fStartAngel = 90;	//饼图开始时的startAngel
	};

}
