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
		float m_fSweepAngel = -120;	//��Ҫ���ƵĻ���ֵ��Ӧ��Ϊ 0-360�ȷ�Χ��
		float m_fStartAngel = 90;	//��ͼ��ʼʱ��startAngel
	};

}
