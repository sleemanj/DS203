#ifndef __MENUWINDOW_H__
#define __MENUWINDOW_H__

class CItemWindow : public CWndMenuItem
{
	CSettings::TimeBase* m_pInfo;
	CProviderNum	m_proTime;

public:
	virtual void Create(CSettings::TimeBase* pInfo, CWnd *pParent)
	{
		_ASSERT(pInfo);
		m_pInfo = pInfo;

		CWndMenuItem::Create( "", RGB565(ffffff), 1, pParent);
		m_proTime.Create( &Settings.Time.Shift, Settings.Time.InvalidFirst, 4096 - CWndGraph::BlkX * CWndGraph::DivsX );
	}


	virtual void OnPaint()
	{
		ui16 clr = RGB565(000000);
		CWndMenuItem::OnPaint();
		int x = m_rcClient.left + 8 + MarginLeft;
		int y = m_rcClient.top;
		const char* szUnitNames[]=
		{ "ns", "us", "ms", "s" };
		enum { _ns= 0, _us, _ms, _s } units;

		y += 1;
		double timeOffset = (m_proTime.Get() - Settings.Time.InvalidFirst) * 
			CSettings::TimeBase::pfValueResolution[m_pInfo->Resolution] / (CWndGraph::BlkX);
		if (timeOffset < .95E-6)
		{
			timeOffset *= (double)1E9;
			units = _ns;
		}
		else if (timeOffset <= .95E-3)
		{
			timeOffset *= (double)1E6;
			units = _us;
		}
		else if (timeOffset <= 0.95) {
			timeOffset *= (double)1E3;
			units = _ms;
		}
		else 
		{
			units = _s;
		}

		if (HasFocus())
		{
			x -= 8;
			x += BIOS::LCD::Draw(x, y, clr, RGBTRANS, CShapes::sel_left);
			x += BIOS::LCD::Print(x, y, RGBTRANS, clr, (timeOffset >= 0 ? "+" : "-"));
			x += BIOS::LCD::Print(x, y, RGBTRANS, clr, CUtils::itoa((si16)(timeOffset + 0.5)));
			x += BIOS::LCD::Print(x, y, RGBTRANS, clr, szUnitNames[units] );
			x += BIOS::LCD::Draw(x, y, clr, RGBTRANS, CShapes::sel_right);
		}
		else
		{
			
			x += BIOS::LCD::Print(x, y, clr, RGBTRANS, (timeOffset >= 0 ? "+": "-"));
			x += BIOS::LCD::Print(x, y, clr, RGBTRANS, CUtils::itoa((si16)(timeOffset + 0.5)));
			x += BIOS::LCD::Print(x, y, clr, RGBTRANS, szUnitNames[units]);
		}
	}


	virtual void OnKey(ui16 nKey)
	{
		int nMin = Settings.Time.InvalidFirst;
		m_proTime.SetMin(nMin);

		if ( nKey & BIOS::KEY::KeyLeft && m_proTime-1 == CValueProvider::Yes )
		{
			for (ui8 t = 0; t<CWndGraph::BlkX && m_proTime - 1 == CValueProvider::Yes; t++)
				m_proTime--;
			Invalidate();
			SendMessage(m_pParent, ToWord('w', 'u'), 0);
		}
		if ( nKey & BIOS::KEY::KeyRight && m_proTime+1 == CValueProvider::Yes )
		{
			for (ui8 t = 0; t<CWndGraph::BlkX && m_proTime + 1 == CValueProvider::Yes; t++)
				m_proTime++;
			Invalidate();
			SendMessage(m_pParent, ToWord('w', 'u'), 0);
		}

		CWnd::OnKey( nKey );
	}

};

#endif