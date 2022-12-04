void clear()
{
    if(m_formLayout)
    {
        QLayoutItem *child;
        while ((child = m_formLayout->takeAt(0)) != 0)
        {
            QLayout     * layout = child->layout();
            QSpacerItem * spacer = child->spacerItem();
            QWidget     * widget = child->widget();

            if(layout && !doesOwnObject(layout)) delete layout;
            if(spacer && !doesOwnObject(spacer)) delete spacer;
            if(widget && !doesOwnObject(widget)) delete widget;
        }

        delete m_formLayout;
        m_formLayout = 0L;
    }
}
