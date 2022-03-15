class CWaitDialog : public CDialog
{
protected:
	BOOL* m_pFlag;
public:
	CWaitDialog(BOOL*, LPCTSTR dialogTitle = NULL, LPCTSTR dialogText = NULL);
	virtual ~CWaitDialog();
	virtual void OnCancel();
	BOOL Pump();
	void SetPercentComplete(int);
	void SetPercentCompleteAndPump(int);
	void SetMessageText(LPCTSTR);
	void Close();
	bool Cancel() const;    // did user press cancel button?
};