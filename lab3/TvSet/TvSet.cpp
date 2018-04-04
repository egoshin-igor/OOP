#include "stdafx.h"
#include "TvSet.h"

bool TvSet::IsTurnedOn() const
{
	return m_isOn;
}

void TvSet::TurnOn()
{
	m_isOn = true;
}

void TvSet::TurnOff()
{
	m_isOn = false;
}

int TvSet::GetChannel() const
{
	return m_isOn ? m_selectedChannel : 0;
}

bool TvSet::SelectChannel(int channel)
{
	bool possibleChannel = channel >= 1 && channel <= 99;
	if (possibleChannel && m_isOn)
	{
		m_selectedChannel = channel;
		return true;
	}
	else
	{
		return false;
	}
}