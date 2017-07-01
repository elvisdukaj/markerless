#pragma once

#include "abstractopencvrunnablefilter.h"
#include "patterndetector.h"

class PatternDetectorFilter : public QAbstractVideoFilter {
    Q_OBJECT

public:
    QVideoFilterRunnable* createFilterRunnable() override;

signals:
    void objectFound();

private:
    friend class ObjectFilterRunnable;

private:
    QString m_patternImageFilename;
};

class PatternDetectorFilterRunnable : public AbstractVideoFilterRunnable {
public:
    PatternDetectorFilterRunnable(PatternDetectorFilter* filter);
    QVideoFrame run(QVideoFrame* input, const QVideoSurfaceFormat &surfaceFormat, RunFlags flags) override;

private:
    void loadImagePattern(QString filename);

private:
    PatternDetectorFilter* m_filter;
    cv::Mat m_patternImage;
    PatternDetector m_detecter;
};
