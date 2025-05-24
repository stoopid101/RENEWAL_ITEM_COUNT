Search
//
void CSlotWindow::SetSlotCount(DWORD dwIndex, DWORD dwCount)
//
Change
//
void CSlotWindow::SetSlotCount(DWORD dwIndex, DWORD dwCount)
{
    TSlot * pSlot;
    if (!GetSlotPointer(dwIndex, &pSlot))
        return;

    if (dwCount <= 0)
    {
        if (pSlot->pNumberLine)
        {
            delete pSlot->pNumberLine;
            pSlot->pNumberLine = NULL;
        }
    }
    else
    {
        std::string szCount;
            DWORD index = 0;

        DWORD modIndex = 1;
        while (dwCount > 0)
        {
            if ((index + 1) % 4 == 0)
            {

                if (modIndex == 1)
                    szCount = "k" + szCount;
                else if (modIndex == 2)
                    szCount = "m" + szCount;
                else
                    szCount = "t" + szCount;
                modIndex++;
            }
            else
            {
                szCount = std::to_string(dwCount % 10) + szCount;
                dwCount /= 10;
            }

            index++;
        }

        std::string::reverse_iterator checkPoint = szCount.rbegin();
        for (auto it = szCount.rbegin(); it != szCount.rend(); it++)
        {
            if (it == '0')
            {
                continue;
            }
            if (it >= '1' && it <= '9')
            {
                break;
            }
            else // k m t
            {
                checkPoint = it;
            }
        }

        if (checkPoint != szCount.rbegin())
        {
            szCount.erase(checkPoint.base(), szCount.end());
        }

        if (!pSlot->pNumberLine)
        {
            CNumberLine pNumberLine = new UI::CNumberLine(this);
            pNumberLine->SetHorizontalAlign(CNumberLine::HORIZONTAL_ALIGN_RIGHT);
            pNumberLine->Show();
            pSlot->pNumberLine = pNumberLine;
        }

        pSlot->pNumberLine->SetNumber(szCount.c_str());
    }
}
//