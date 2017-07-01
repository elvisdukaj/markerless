#pragma once

#include "abstractopencvrunnablefilter.h"
#include "patterndetector.h"

class PatternDetectorFilter : public QAbstractVideoFilter {
    Q_OBJECT

    Q_PROPERTY(int showMatches READ showMatches WRITE showMatches)
    Q_PROPERTY(int patternFound NOTIFY patternFound)
    Q_PROPERTY(int minNumberMatchesAllowed READ minNumberMatchesAllowed WRITE minNumberMatchesAllowed)

public:
    QVideoFilterRunnable* createFilterRunnable() override;

    int showMatches() const noexcept { return m_showMatch; }
    void showMatches(int show) noexcept { m_showMatch = show; }

    int minNumberMatchesAllowed() const noexcept { return m_minNumberMatchesAllowed; }
    void minNumberMatchesAllowed(int c) noexcept { m_minNumberMatchesAllowed = c; }

signals:
    void patternFound(int keypoints);

private:
    friend class ObjectFilterRunnable;

private:
    QString m_patternImageFilename;
    int m_minNumberMatchesAllowed;
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
