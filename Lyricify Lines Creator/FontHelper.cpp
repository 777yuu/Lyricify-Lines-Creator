#include "FontHelper.h"

SIZE FontHelper::CalculateTextSize(const wchar_t* text, const wchar_t* fontName, int fontSize, int dpiScale, int fontWeight, bool italic, bool underline, bool strikeout)
{
    SIZE textSize = { 0 };

    if (text && fontName && fontSize > 0)
    {
        // ��������
        HFONT hFont = CreateFont(fontSize * dpiScale, 0, 0, 0, fontWeight, italic, underline, strikeout, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH, fontName);

        if (hFont)
        {
            HDC hdc = GetDC(NULL);
            if (hdc)
            {
                HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);

                // ʹ�� DrawText ���������ı��ߴ�
                RECT rect = { 0, 0, 0, 0 };
                DrawText(hdc, text, -1, &rect, DT_CALCRECT);

                textSize.cx = (rect.right - rect.left) / dpiScale;
                textSize.cy = (rect.bottom - rect.top) / dpiScale;

                // �ָ�ԭ��������
                SelectObject(hdc, hOldFont);
                ReleaseDC(NULL, hdc);
            }

            // �ͷ�������Դ
            DeleteObject(hFont);
        }
    }

    return textSize;
}