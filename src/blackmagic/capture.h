#ifndef __CAPTURE_H__
#define __CAPTURE_H__

#include "include/DeckLinkAPI.h"

#include <QWidget>
#include <QObject>
#include <QLayout>

class CDeckLinkGLWidget;
class PlaybackDelegate;

class DeckLinkCaptureDelegate : public IDeckLinkInputCallback
{
public:
	DeckLinkCaptureDelegate();
	virtual ~DeckLinkCaptureDelegate();

	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID /*iid*/, LPVOID */*ppv*/) { return E_NOINTERFACE; }
	virtual ULONG STDMETHODCALLTYPE AddRef(void);
	virtual ULONG STDMETHODCALLTYPE  Release(void);
	virtual HRESULT STDMETHODCALLTYPE VideoInputFormatChanged(BMDVideoInputFormatChangedEvents, IDeckLinkDisplayMode*, BMDDetectedVideoInputFormatFlags);
	virtual HRESULT STDMETHODCALLTYPE VideoInputFrameArrived(IDeckLinkVideoInputFrame*, IDeckLinkAudioInputPacket*);

private:
	ULONG				m_refCount;
	pthread_mutex_t		m_mutex;
};

class CaptureHandler
{
public:
	CaptureHandler(QVBoxLayout *lay, QWidget *parent = 0);
	~CaptureHandler();
	CDeckLinkGLWidget *previewView;
	void startPreview(int deviceId, int captureMode);
	void stopPreview();
	void startCapture();
	void stopCapture();
	void captureFrame(const QString &fname);
	void showOverlay(QImage img, bool transparent = true);
	void hideOverlay();
	void hidePreview(bool hide);
	
private:
  	IDeckLinkIterator		*deckLinkIterator;
	DeckLinkCaptureDelegate 	*delegate;
	IDeckLinkDisplayMode		*displayMode;
	IDeckLink			*deckLink;
	IDeckLinkInput			*deckLinkInput;
	IDeckLinkDisplayModeIterator	*displayModeIterator;
	QVBoxLayout *m_layout;
	QWidget *m_parent;
};


#endif
