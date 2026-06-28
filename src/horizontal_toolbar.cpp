#include <QCheckBox>
#include <QColorDialog>
#include <QDoubleSpinBox>
#include <QIcon>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>
#include <QToolBar>

#include "main_window.h"

void MainWindow::MakeHorizontalToolbarButton(QPushButton *button, QString icon_path,
                                             QString tooltip) {
  button->setIcon(LoadIcon(icon_path));
  button->setIconSize(QSize(24, 24));
  button->setToolTip(tooltip);
  button->setFocusPolicy(Qt::NoFocus);
  button->setFixedSize(32, 32);
}

void MainWindow::CreateHorizontalToolbar() {
  QToolBar *horizontalToolbar = new QToolBar("Horizontal Tools");
  horizontalToolbar->setMovable(false);
  horizontalToolbar->setContextMenuPolicy(Qt::PreventContextMenu);
  addToolBar(Qt::TopToolBarArea, horizontalToolbar);

  // Create all buttons
  QPushButton *saveButton = new QPushButton();
  MakeHorizontalToolbarButton(saveButton, "icons/horizontal/save.svg", "Save");

  QPushButton *openButton = new QPushButton();
  MakeHorizontalToolbarButton(openButton, "icons/horizontal/open.svg", "Open");

  QPushButton *undoButton = new QPushButton();
  MakeHorizontalToolbarButton(undoButton, "icons/horizontal/undo.svg", "Undo");

  QPushButton *redoButton = new QPushButton();
  MakeHorizontalToolbarButton(redoButton, "icons/horizontal/redo.svg", "Redo");

  QPushButton *cutButton = new QPushButton();
  MakeHorizontalToolbarButton(cutButton, "icons/horizontal/cut.svg", "Cut");

  QPushButton *copyButton = new QPushButton();
  MakeHorizontalToolbarButton(copyButton, "icons/horizontal/copy.svg", "Copy");

  QPushButton *pasteButton = new QPushButton();
  MakeHorizontalToolbarButton(pasteButton, "icons/horizontal/paste.svg", "Paste");

  QCheckBox *fillCheckbox = new QCheckBox();
  fillCheckbox->setChecked(document_->has_fill_);
  fillCheckbox->setToolTip("Fill");
  fillCheckbox->setFocusPolicy(Qt::NoFocus);

  QPushButton *fillColorButton = new QPushButton();
  MakeHorizontalToolbarButton(fillColorButton, "icons/horizontal/fill_color.svg", "Fill Color");

  QPushButton *strokeColorButton = new QPushButton();
  MakeHorizontalToolbarButton(strokeColorButton, "icons/horizontal/stroke_color.svg",
                              "Stroke Color");

  QLabel *widthLabel = new QLabel("W:");

  QDoubleSpinBox *strokeWidthSpinBox = new QDoubleSpinBox();
  strokeWidthSpinBox->setRange(0.1, 50.0);
  strokeWidthSpinBox->setSingleStep(0.5);
  strokeWidthSpinBox->setValue(document_->stroke_width_);
  strokeWidthSpinBox->setMaximumWidth(60);
  strokeWidthSpinBox->setToolTip("Stroke Width");
  strokeWidthSpinBox->setFocusPolicy(Qt::NoFocus);

  QLabel *fontSizeLabel = new QLabel(" Font:");

  QSpinBox *fontSizeSpinBox = new QSpinBox();
  fontSizeSpinBox->setRange(6, 300);
  fontSizeSpinBox->setSingleStep(2);
  fontSizeSpinBox->setValue(document_->font_size_);
  fontSizeSpinBox->setMaximumWidth(60);
  fontSizeSpinBox->setToolTip("Font Size");
  fontSizeSpinBox->setFocusPolicy(Qt::NoFocus);

  // Add all buttons to toolbar
  horizontalToolbar->addWidget(saveButton);
  horizontalToolbar->addWidget(openButton);
  horizontalToolbar->addSeparator();
  horizontalToolbar->addWidget(undoButton);
  horizontalToolbar->addWidget(redoButton);
  horizontalToolbar->addSeparator();
  horizontalToolbar->addWidget(cutButton);
  horizontalToolbar->addWidget(copyButton);
  horizontalToolbar->addWidget(pasteButton);
  horizontalToolbar->addSeparator();
  horizontalToolbar->addWidget(fillCheckbox);
  horizontalToolbar->addWidget(fillColorButton);
  horizontalToolbar->addSeparator();
  horizontalToolbar->addWidget(strokeColorButton);
  horizontalToolbar->addWidget(widthLabel);
  horizontalToolbar->addWidget(strokeWidthSpinBox);
  horizontalToolbar->addSeparator();
  horizontalToolbar->addWidget(fontSizeLabel);
  horizontalToolbar->addWidget(fontSizeSpinBox);

  // Connect all signals
  connect(saveButton, &QPushButton::clicked, [this]() {
    file_manager_->SaveFile(document_);
    Refresh();
  });
  connect(openButton, &QPushButton::clicked, [this]() {
    file_manager_->OpenFile(document_);
    Refresh();
  });
  connect(undoButton, &QPushButton::clicked, [this]() {
    document_->Undo();
    Refresh();
  });
  connect(redoButton, &QPushButton::clicked, [this]() {
    document_->Redo();
    Refresh();
  });
  connect(cutButton, &QPushButton::clicked, [this]() {
    document_->Cut();
    Refresh();
  });
  connect(copyButton, &QPushButton::clicked, [this]() {
    document_->Copy();
    Refresh();
  });
  connect(pasteButton, &QPushButton::clicked, [this]() {
    if (document_->clipboard_ == nullptr) return;
    document_->Paste(document_->clipboard_->GetCenter() + QPointF(10, 10));
    Refresh();
  });
  connect(fillCheckbox, &QCheckBox::toggled, [this](bool checked) {
    document_->has_fill_ = checked;
    update();
  });
  connect(fillColorButton, &QPushButton::clicked, [this, fillColorButton]() {
    QColor color = QColorDialog::getColor(document_->fill_color_, this);
    if (color.isValid()) {
      document_->fill_color_ = color;
    }
  });
  connect(strokeColorButton, &QPushButton::clicked, [this, strokeColorButton]() {
    QColor color = QColorDialog::getColor(document_->stroke_color_, this);
    if (color.isValid()) {
      document_->stroke_color_ = color;
    }
  });
  connect(strokeWidthSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
          [this](double value) { document_->stroke_width_ = value; });
  connect(fontSizeSpinBox, QOverload<int>::of(&QSpinBox::valueChanged),
          [this](int value) { document_->font_size_ = value; });
}
