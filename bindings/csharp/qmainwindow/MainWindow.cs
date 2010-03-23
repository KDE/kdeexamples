
using System;
using Qyoto;

namespace qyoto_example
{


	public class MainWindow : QMainWindow
	{
		public MainWindow ()
		{
			m_layout = new QHBoxLayout();
			m_label = new QLabel("Hello Qyoto!");
			m_widget = new QWidget(this);
		
			m_layout.AddWidget(m_label);
			m_widget.SetLayout(m_layout);
		
			SetCentralWidget(m_widget);
		}
			
		private QHBoxLayout m_layout;
		private QLabel m_label;
		private QWidget m_widget;
	}
}
