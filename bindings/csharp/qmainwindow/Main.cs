using System;
using Qyoto;
namespace qyoto_example
{

	class MainClass
	{
		public static int Main (string[] args)
		{
			QApplication app = new QApplication(args);
			MainWindow w = new MainWindow();
			w.Show();
			
			return QApplication.Exec();
		}
	}
}
