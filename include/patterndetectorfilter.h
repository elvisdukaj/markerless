#pragma once

#include "abstractopencvrunnablefilter.h"
#include "patterndetector.h"

class PatternDetectorFilter : public QAbstractVideoFilter {
    Q_OBJECT

    Q_PROPERTY(int showMatches READ showMatches WRITE showMatches)
    Q_PROPERTY(int patternFound NOTIFY patternFound)
public:
    QVideoFilterRunnable* createFilterRunnable() override;

    int showMatches() const noexcept { return m_showMatch; }
    void showMatches(int show) noexcept { m_showMatch = show; }

signals:
    void patternFound(int keypoints);

private:
    friend class ObjectFilterRunnable;

private:
    QString m_patternImageFilename;
    bool m_showMatch;
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
